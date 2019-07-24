#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "PlayingState.h"

namespace Entities
{
    class Ball : public Entity
    {
        public:
            Ball(sf::Vector2<double>, int, sf::Color, State::Playing*);

            void input  (const sf::Event& e);
            void input  ();
            void update (double dt);
            void draw   ();

        private:
            sf::Vector2<double> m_position;
            sf::Vector2<double> m_velocity;
            int m_species;
            sf::Color m_color;
            State::Playing* m_state;
    };
}