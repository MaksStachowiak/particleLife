#include "Ball.h"

#include "Application.h"
#include "Display.h"
#include "Random.h"

#include <iostream>

#include "PlayingState.h"
#include "Physics.h"

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
    void Ball::update (double dt)
    {   
        // bounce back from edges of screen
        if (m_position.x < 0)
            m_velocity.x -= m_position.x;
        if (m_position.y < 0)
            m_velocity.y -= m_position.y;
        if (m_position.x > Display::WIDTH)
            m_velocity.x -= m_position.x - Display::WIDTH;
        if (m_position.y > Display::HEIGHT)
            m_velocity.y -= m_position.y - Display::HEIGHT;

        // calculate forces and update velocity
        for(int i = 0; i < m_state->ballPositions.size(); i++)
        {
            m_velocity += Physics::getForce(m_state->ballPositions[i], m_position);
        }
        m_velocity *= 0.985; // friction

        // update position
        auto movement = m_velocity * (dt * 20);
        m_position += movement;
    }
    
    void Ball::draw   ()
    {
        // draw the ball
        sf::CircleShape circle(BALL_RADIUS);
        circle.setFillColor(color);
        circle.setPosition(m_position.x-BALL_RADIUS, m_position.y-BALL_RADIUS);
        Display::draw(circle);

        // debug options
        if (m_state->debugShowVelocity)
        {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0] = sf::Vertex(sf::Vector2f(m_position));
            line[0].color  = sf::Color::Red;
            line[1] = sf::Vertex(sf::Vector2f(m_position) + sf::operator*(sf::Vector2f(m_velocity), 20.f));
            line[1].color  = sf::Color::Red;
            Display::draw(line);
        }

        if (m_state->debugShowRadii)
        {
            sf::CircleShape outline(BALL_RADIUS*8);
            outline.setFillColor(sf::Color(0, 0, 0, 0));
            outline.setOutlineThickness(1);
            outline.setOutlineColor(sf::Color(150, 150, 150));
            outline.setPosition(m_position.x-BALL_RADIUS*8, m_position.y-BALL_RADIUS*8);
            Display::draw(outline);
        }
    }
}