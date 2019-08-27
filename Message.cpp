#include "Message.h"

#include "Display.h"
#include "PlayingState.h"

namespace Entities
{
    Message::Message(std::string text_string, int position, State::Playing* state)
    : Entity()
    , m_state(state)
    , m_time_to_live(MESSAGE_LIFESPAN)
    , m_position(position)
    {
        font_ptr = Display::getFont();
        sf::Text text(text_string, *font_ptr, FONT_SIZE);
        text_ptr = std::make_unique<sf::Text>(text_string, *font_ptr, FONT_SIZE);
        text_ptr->setFillColor(sf::Color(255,255,255,255));
        text_ptr->setPosition(sf::Vector2f(0, static_cast<int>(m_position)));
    }

    void Message::input  (const sf::Event& e)
    { }
    void Message::input  ()
    { }
    void Message::update (double dt)
    {
        m_time_to_live -= dt;
        text_ptr->setFillColor(sf::Color(255,255,255,255*(m_time_to_live/MESSAGE_LIFESPAN)));

        if (m_time_to_live < 0)
            m_state->messagesToDelete++;
    }  
    void Message::draw   ()
    {
        Display::draw(*text_ptr);
    }

    void Message::pushDown()
    {
        m_position += FONT_SIZE;
        text_ptr->setPosition(sf::Vector2f(0, m_position));
    }

}