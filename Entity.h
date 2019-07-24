#pragma once

#include <SFML/Graphics.hpp>

namespace Entities
{
    class Entity
    {
        public:
            Entity();
            virtual ~Entity() = default;

            virtual void input  (const sf::Event& e) = 0;
            virtual void input  () = 0;
            virtual void update (double dt) = 0;
            virtual void draw   () = 0;
    };
}