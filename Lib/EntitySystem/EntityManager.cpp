#include "EntityManager.hpp"
#include "Entity.hpp"
#include "System.hpp"

namespace es
{

EntityManager::EntityManager()
{
}

Entity::Ptr EntityManager::create()
{
    mEntities.push_back(std::make_shared<Entity>());
    mEntities.back()->mManager = this;
    return mEntities.back();
}

Entity::Ptr EntityManager::get(std::size_t id) const
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (mEntities[i]->getId() == id)
            {
                return mEntities[i];
            }
        }
    }
    return nullptr;
}

EntityArray EntityManager::getByFilter(ComponentFilter const& filter) const
{
    EntityArray array;
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (mEntities[i]->hasComponents(filter))
            {
                array.push_back(mEntities[i]);
            }
        }
    }
    return array;
}

EntityArray EntityManager::getAll() const
{
    return mEntities;
}

void EntityManager::remove(EntityPtr e)
{
    mEntitiesToRemove.push_back(e);
}

void EntityManager::remove(std::size_t id)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (id == mEntities[i]->getId())
            {
                mEntitiesToRemove.push_back(mEntities[i]);
            }
        }
    }
}

void EntityManager::removeAll()
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        mEntitiesToRemove.push_back(mEntities[i]);
    }
}

void EntityManager::update()
{
    for (unsigned int i = 0; i < mEntitiesToRemove.size(); i++)
    {
        for (auto itr = mSystems.begin(); itr != mSystems.end(); ++itr)
        {
            itr->second->remove(mEntitiesToRemove[i]);
        }
        for (unsigned int j = 0; j < mEntities.size(); j++)
        {
            if (mEntities[j] == mEntitiesToRemove[i])
            {
                mEntities.erase(mEntities.begin() + j);
            }
        }
    }
}

bool EntityManager::hasSystem(std::string const& type) const
{
    return mSystems.find(type) != mSystems.end();
}

void EntityManager::removeSystems()
{
    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
    {
        itr->second->mEntities.clear();
        itr->second->mManager = nullptr;
        delete itr->second;
        mSystems.erase(itr);
    }
    mSystems.clear();
}

std::size_t EntityManager::getEntitiesCount() const
{
    return mEntities.size();
}

void EntityManager::reset()
{
    removeAll();
    removeSystems();
    Entity::gIdCounter = 0;
}

void EntityManager::updateEntity(std::size_t id, UpdateEntity type)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i]->getId() == id)
        {
            auto e = mEntities[i];
            switch (type)
            {
                case AddComponent:
                {
                    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
                    {
                        if (!itr->second->has(e) && e->hasComponents(itr->second->getFilter()))
                        {
                            itr->second->mEntities.push_back(e);
                        }
                    }
                } break;

                case RemoveComponent:
                {
                    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
                    {
                        if (itr->second->has(e) && !e->hasComponents(itr->second->getFilter()))
                        {
                            for (unsigned int i = 0; i < itr->second->mEntities.size(); i++)
                            {
                                if (itr->second->mEntities[i] == e)
                                {
                                    itr->second->mEntities.erase(itr->second->mEntities.begin() + i);
                                    return;
                                }
                            }
                        }
                    }
                } break;

                case RemoveComponents:
                case RemoveEntity:
                {
                    for (auto itr = mSystems.begin(); itr != mSystems.end(); itr++)
                    {
                        if (itr->second->has(e))
                        {
                            for (unsigned int i = 0; i < itr->second->mEntities.size(); i++)
                            {
                                if (itr->second->mEntities[i] == e)
                                {
                                    itr->second->mEntities.erase(itr->second->mEntities.begin() + i);
                                }
                            }
                        }
                    }
                } break;
            }
            return;
        }
    }
}

void EntityManager::updateSystem(System* s, ComponentFilter const& filter)
{
    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        if (mEntities[i] != nullptr)
        {
            if (mEntities[i]->hasComponents(filter))
            {
                s->mEntities.push_back(mEntities[i]);
            }
        }
    }
}

}
