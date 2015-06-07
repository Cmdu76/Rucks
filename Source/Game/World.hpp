#ifndef WORLD_HPP
#define WORLD_HPP

#include "../../Lib/Aharos/Application.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/View.hpp>

#include "ChunkManager.hpp"
#include "ObjectManager.hpp"
#include "../Base/Chat.hpp"

class OnlineManager;

class World : public sf::Drawable
{
    public:
        World(bool online);
        ~World();

        void handleEvent(sf::Event const& event);
        void update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        ah::Application& getApplication();
        ChunkManager& getChunkManager();
        ObjectManager& getObjectManager();
        OnlineManager& getOnlineManager();
        Chat& getChat();
        sf::View& getView();
        Player::Ptr getPlayer();

        bool isOnline();

    private:
        ChunkManager mChunkManager;
        ObjectManager mObjectManager;
        OnlineManager& mOnlineManager;
        Chat mChat;
        sf::View mView;
        bool mOnline;
};

#endif // WORLD_HPP
