#pragma once

#include "StateBase.h"
#include "Physics.h"

namespace State
{
    class Menu : public StateBase
    {
        public:
            Menu (Application& application);
            Menu (Application& application, std::vector<std::vector<Physics::interactionRules>>, std::vector<sf::Color>);

            void input      (const sf::Event& e);
            void input      ();
            void update     (double dt);
            void draw       ();

            std::vector<std::vector<Physics::interactionRules>> currentRules;
            std::vector<sf::Color> currentColors;
    };
}
