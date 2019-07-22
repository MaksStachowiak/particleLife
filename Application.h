#pragma once

// #include <SFML/Audio/Music.hpp>

#include <memory>

#include <stack>

// #include "Resource_Managers/Resource_Holder.h"
#include "StateBase.h"

class Application
{
    public:
        Application();

        void runMainLoop();

        void pushState(std::unique_ptr<State::StateBase> state);
        void popState ();

    private:
        std::stack<std::unique_ptr<State::StateBase>> m_states;

        // sf::Music m_music;

};