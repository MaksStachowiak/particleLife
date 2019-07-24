#pragma once

// #include <SFML/Audio/Music.hpp>

#include <memory>

#include <stack>

// #include "Resource_Managers/Resource_Holder.h"
#include "StateBase.h"

const double BALL_RADIUS = 5; 

class Application
{
    public:
        Application();

        void runMainLoop();

        void pushState(std::unique_ptr<State::StateBase> state);
        void popState ();

        void debugInput(const sf::Event& e);
        void debugUpdate();

    private:
        std::stack<std::unique_ptr<State::StateBase>> m_states;
        
        bool debugMousePos;
        bool debugFPS;
        // sf::Music m_music;

};