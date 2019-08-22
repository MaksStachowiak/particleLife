#pragma once

#include <SFML/Graphics.hpp>

class Application;

namespace State
{
    class StateBase
    {
        public:
            StateBase(Application& application);
            virtual ~StateBase() = default;

            virtual void input  (const sf::Event& e)    = 0;
            virtual void input  ()                      = 0;
            virtual void update (double dt)             = 0;
            virtual void draw   ()                      = 0;

        protected:
            Application* m_p_application;

    };
}
