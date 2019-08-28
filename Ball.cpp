#include "Ball.h"

#include "Application.h"
#include "Display.h"
#include "Random.h"

#include <iostream>

#include "PlayingState.h"
#include "Physics.h"


namespace Entities
{
    Ball::Ball(sf::Vector2<double> position, int species, sf::Color color, State::Playing* state)
    : Entity()
    , m_position (position)
    , m_species(species)
    , m_color(color)
    , m_state(state)
    {
        m_velocity = sf::Vector2<double>(Random::randomDouble()-0.5,Random::randomDouble()-0.5);
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
            m_velocity.x -= m_position.x*Physics::EDGE_BOUNCE;
        if (m_position.y < 0)
            m_velocity.y -= m_position.y*Physics::EDGE_BOUNCE;
        if (m_position.x > Display::WIDTH)
            m_velocity.x -= (m_position.x - Display::WIDTH)*Physics::EDGE_BOUNCE;
        if (m_position.y > Display::HEIGHT)
            m_velocity.y -= (m_position.y - Display::HEIGHT)*Physics::EDGE_BOUNCE;

        // calculate forces and update velocity
        for(int i = 0; i < m_state->ballPositions.size(); i++)
        {
            m_velocity += Physics::getForce(m_state->ballPositions[i], m_position,
            m_state->interactionCharacteristics[m_species][m_state->ballSpecies[i]]);
        }
        m_velocity *= Physics::FRICTION;

        // update position
        auto movement = m_velocity * (dt * 20);
        m_position += movement;
    }
    
    void Ball::draw   ()
    {
        // draw the ball
        sf::CircleShape circle(BALL_RADIUS);
        circle.setFillColor(m_color);
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
            if (m_state->getSpeciesSelection() == -1)
                for(int i=0; i<m_state->interactionCharacteristics.size(); i++)
                    Display::draw(interactionRange(m_species, i));
            else
                Display::draw(interactionRange(m_species, m_state->getSpeciesSelection()));
        }
    }

    sf::CircleShape Ball::interactionRange(int a, int b)
    {
        double r = m_state->interactionCharacteristics[a][b].maxRadius;
        sf::CircleShape outline(r);
        outline.setFillColor(sf::Color(0, 0, 0, 0));
        outline.setOutlineThickness(1);
        outline.setOutlineColor(m_state->speciesColors[b]);
        outline.setPosition(m_position.x-r, m_position.y-r);
        return outline;
    }
}