#ifndef ES_ENTITYMANAGER_HPP
#define ES_ENTITYMANAGER_HPP

#include <algorithm>
#include <cassert>
#include <map>
#include <memory>

#include "Component.hpp"

namespace es
{

class Entity;
class System;

typedef std::shared_ptr<Entity> EntityPtr;
typedef std::vector<EntityPtr> EntityArray;
typedef std::map<std::string,System*> SystemArray;

class EntityManager
{
    public:
        friend class Entity;
        friend class System;

        enum UpdateEntity
        {
            AddComponent,
            RemoveComponent,
            RemoveComponents,
            RemoveEntity,
        };

    public:
        EntityManager();

        EntityPtr create();

        // Entity Management
        EntityPtr get(std::size_t id) const;
        EntityArray getByFilter(ComponentFilter const& filter) const;
        EntityArray getAll() const;

        void remove(EntityPtr e);
        void remove(std::size_t id);
        void removeAll();

        void update(); // Remove EntitiesToRemove

        // System Management
        template<typename T>
        T& addSystem(T* system = nullptr);

        template<typename T>
        bool hasSystem() const;
        bool hasSystem(std::string const& type) const;

        template<typename T>
        void removeSystem();
        void removeSystems();

        template<typename T>
        T& getSystem();

        std::size_t getEntitiesCount() const;
        void reset();

    protected:
        void updateEntity(std::size_t id, UpdateEntity type);
        void updateSystem(System* s, ComponentFilter const& filter);

    protected:
        EntityArray mEntities;
        SystemArray mSystems;
        EntityArray mEntitiesToRemove;
};


template<typename T>
T& EntityManager::addSystem(T* system)
{
    if (system == nullptr)
    {
        system = new T();
    }

    system->mManager = this;
    mSystems[T::getId()] = system;
    updateSystem(system,system->getFilter());
    return *system;
}

template<typename T>
bool EntityManager::hasSystem() const
{
    return mSystems.find(T::getId()) != mSystems.end();
}

template<typename T>
void EntityManager::removeSystem()
{
    auto itr = mSystems.find(T::getId());
    if (itr != mSystems.end())
    {
        itr->second->mEntities.clear();
        itr->second->mManager = nullptr;
        delete itr->second;
        mSystems.erase(itr);
    }
}

template<typename T>
T& EntityManager::getSystem()
{
    assert(hasSystem<T>());

    return static_cast<T&>(*mSystems[T::getId()]);
}

} // namespace es

#endif // ES_ENTITYMANAGER_HPP
