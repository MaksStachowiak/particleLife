#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

namespace Entities
{
    class Ball : public Entity
    {
        public:
            Ball();

            void input  (const sf::Event& e);
            void input  ();
            void update (float dt);
            void draw   ();
    };
}