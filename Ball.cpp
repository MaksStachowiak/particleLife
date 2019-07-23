#include "Ball.h"

#include "Application.h"
#include "Display.h"
#include "Random.h"

#include <iostream>

#include "PlayingState.h"
#include "Maths.h"

namespace Entities
{
    Ball::Ball(sf::Vector2<double> position, int species, State::Playing* state)
    : Entity()
    , m_position (position)
    , m_species(species)
    , m_state(state)
    {
        m_velocity = sf::Vector2<double>(Random::randomDouble()-0.5,Random::randomDouble()-0.5);
        color = Random::randomColor();
    }

    void Ball::input  (const sf::Event& e)
    { }
    void Ball::input  ()
    { 
        m_state->noticeBall(m_position, m_species);
    }
    void Ball::update (float dt)
    {   
        if (m_position.x < 0)
            m_velocity.x -= m_position.x;
        if (m_position.y < 0)
            m_velocity.y -= m_position.y;
        if (m_position.x > Display::WIDTH)
            m_velocity.x -= m_position.x - Display::WIDTH;
        if (m_position.y > Display::HEIGHT)
            m_velocity.y -= m_position.y - Display::HEIGHT;

        for(int i = 0; i < m_state->positions.size(); i++)
        {
            // std::cout << Maths::distance(m_state->positions[i], m_position)<<std::endl;
            m_velocity += Maths::getForce(m_state->positions[i], m_position, BALL_RADIUS*5);
        }

        m_position += m_velocity;
        m_velocity *= 0.99;
    }
    void Ball::draw   ()
    {
        sf::CircleShape circle(BALL_RADIUS);
        circle.setFillColor(color);
        circle.setPosition(m_position.x-BALL_RADIUS, m_position.y-BALL_RADIUS);
        Display::draw(circle);

        if (m_state->debugShowVelocity)
        {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0] = sf::Vertex(sf::Vector2f(m_position));
            line[0].color  = sf::Color::Red;
            line[1] = sf::Vertex(sf::Vector2f(m_position) + sf::operator*(sf::Vector2f(m_velocity), 20.f));
            line[1].color  = sf::Color::Red;
            Display::draw(line);
        }
    }
}