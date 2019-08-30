#pragma once

// #include <SFML/Audio/Music.hpp>

#include <memory>

#include <stack>

// #include "Resource_Managers/Resource_Holder.h"
#include "StateBase.h"
#include "Config.h"
#include "Physics.h"

class Application
{
    public:
        Application();

        void runMainLoop();

        void pushState(std::unique_ptr<State::StateBase> state);
        void popState ();

        void openMenu(std::vector<std::vector<Physics::interactionRules>>, std::vector<sf::Color>);
        void closeMenu();
        void newSimulation(std::vector<std::vector<Physics::interactionRules>> = {}, std::vector<sf::Color> = {});

        void debugInput(const sf::Event& e);
        void debugUpdate();

    private:
        std::stack<std::unique_ptr<State::StateBase>> m_states;
        
        bool debugMousePos;
        bool debugFPS;
        // sf::Music m_music;

};