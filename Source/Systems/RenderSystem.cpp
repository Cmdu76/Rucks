#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
    mFilter.requires(TransformComponent::getId());
    mFilter.requires(SpriteComponent::getId());

    mRenderDebug = false;
}

std::string RenderSystem::getId()
{
    return "RenderSystem";
}

void RenderSystem::render(sf::RenderTarget& target)
{
    std::sort(mEntities.begin(), mEntities.end(),
    [](es::Entity::Ptr a, es::Entity::Ptr b) -> bool
    {
        float aPos = a->getComponent<TransformComponent>().getPosition().y + a->getComponent<SpriteComponent>().getOrigin().y;
        float bPos = b->getComponent<TransformComponent>().getPosition().y + b->getComponent<SpriteComponent>().getOrigin().y;
        return aPos < bPos;
    });

    for (unsigned int i = 0; i < mEntities.size(); i++)
    {
        sf::RenderStates states;
        states.transform *= mEntities[i]->getComponent<TransformComponent>().getTransform();

        // Weapon
        if (mEntities[i]->hasComponent<WeaponComponent>() && mEntities[i]->hasComponent<MovementComponent>())
        {
            AnimationComponent::Direction dir = mEntities[i]->getComponent<AnimationComponent>().getDirection();
            if (dir == AnimationComponent::Direction::W || dir == AnimationComponent::Direction::N)
            {
                target.draw(mEntities[i]->getComponent<WeaponComponent>(),states);
            }
        }

        // Sprite
        target.draw(mEntities[i]->getComponent<SpriteComponent>(),states);

        // Weapon
        if (mEntities[i]->hasComponent<WeaponComponent>() && mEntities[i]->hasComponent<MovementComponent>())
        {
            AnimationComponent::Direction dir = mEntities[i]->getComponent<AnimationComponent>().getDirection();
            if (dir == AnimationComponent::Direction::S || dir == AnimationComponent::Direction::E)
            {
                target.draw(mEntities[i]->getComponent<WeaponComponent>(),states);
            }
        }

        // Life Bar
        if (mEntities[i]->hasComponent<LifeComponent>())
        {
            target.draw(mEntities[i]->getComponent<LifeComponent>(), states);
        }

        if (mRenderDebug)
        {
            // Collision Box
            if (mEntities[i]->hasComponent<CollisionComponent>())
            {
                target.draw(mEntities[i]->getComponent<CollisionComponent>(), states);
            }

            // Bounding Box
            if (mEntities[i]->hasComponent<TransformComponent>())
            {
                target.draw(mEntities[i]->getComponent<BoxComponent>(), states);
            }
        }
    }
}

void RenderSystem::renderDebug(bool renderDebug)
{
    mRenderDebug = renderDebug;
}


