#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "../Aharos/State.hpp"

#include <map>
#include <Thor/Input/Connection.hpp>

class GameState : public ah::State
{
    public:
        GameState(ah::StateManager& manager);

        static std::string getID();

        bool handleEvent(sf::Event const& event);
        bool update(sf::Time dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void onActivate();
        void onDeactivate();

    private:
        void toPause();

    private:
        std::map<std::string,thor::Connection> mConnections;
};

#endif // GAMESTATE_HPP
