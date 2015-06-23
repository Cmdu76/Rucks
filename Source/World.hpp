#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include "../Lib/Aharos/ResourceHolder.hpp"
#include "../Lib/EntitySystem/EntitySystem.hpp"

#include "Chunk/ChunkManager.hpp"

#include "Server/Server.hpp"

#include "Systems/RenderSystem.hpp"
#include "Systems/PlayerInputSystem.hpp"
#include "Systems/AnimationSystem.hpp"
#include "Systems/AIControllerSystem.hpp"

#include "Components/TransformComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/PlayerInputComponent.hpp"
#include "Components/LifeComponent.hpp"
#include "Components/AIComponent.hpp"

class World
{
    public:
        static World& instance();

        void initialize();
        void terminate();

        bool loadFromFile(std::string const& filename);
        bool saveToFile(std::string const& filename);

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void render(sf::RenderTarget& target);

        ah::ResourceHolder& getResources();
        sf::View& getView();
        ChunkManager& getChunks();
        es::EntityManager& getEntities();

        bool isOnline() const;
        bool isServer() const;

    private:
        World();
        ~World();

        static World mInstance;

        ah::ResourceHolder mResources;
        sf::View mView;
        ChunkManager mChunks;
        es::EntityManager mEntities;

        bool mIsOnline;
        bool mIsServer;

        Server mServer;
};

#endif // WORLD_HPP
