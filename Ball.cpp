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
        // std::cout << "New ball!" << std::endl;
    }

    void Ball::input  (const sf::Event& e)
    { }
    void Ball::input  ()
    { 
        m_state->noticeBall(m_position, m_species);
    }
    void Ball::update (float dt)
    {   
        for(int i = 0; i < m_state->positions.size(); i++)
        {
            // double distance = Maths::distance(m_state->xs[i], m_state->ys[i], m_position);
            // Maths::normalise(m_state->xs[i]-posX, m_state->ys[i]-posY);
        }

        m_position += m_velocity;
    }
    void Ball::draw   ()
    {
        sf::CircleShape circle(BALL_RADIUS);
        circle.setFillColor(color);
        circle.setPosition(m_position.x, m_position.y);
        Display::draw(circle);
    }
}