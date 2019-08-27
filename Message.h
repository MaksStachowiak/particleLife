#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"

namespace State
{
    class Playing;
}

namespace Entities
{
    class Message : public Entity
    {
        public:
            Message(std::string, int, State::Playing*);

            void input  (const sf::Event& e);
            void input  ();
            void update (double dt);
            void draw   ();

            void pushDown ();
        
        private:
            State::Playing* m_state;
            std::unique_ptr<sf::Text> text_ptr;
            sf::Font* font_ptr;
            double m_time_to_live;
            int m_position;
    };
}
