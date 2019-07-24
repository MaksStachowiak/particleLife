#include "PlayingState.h"

#include "Application.h"
#include "Display.h"
#include "Random.h"
#include "Physics.h"

#include "Entity.h"
#include "Ball.h"

#include <iostream>

namespace State
{
    Playing::Playing(Application& application)
    : StateBase     (application)
    , debugShowVelocity (false)
    , debugShowRadii    (false)
    {
        createSpecies(5);
        populate(500);
        std::cout<<"Now playing"<<std::endl;
    }

    void Playing::input(const sf::Event& e)
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                addBall( static_cast <double> (e.mouseButton.x - BALL_RADIUS),
                         static_cast <double> (e.mouseButton.y - BALL_RADIUS) );
            }
        }
        if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::F3)
            {
                std::cout << m_entities.size() << std::endl;
            }
            if (e.key.code == sf::Keyboard::F4)
            {
                debugShowVelocity = !debugShowVelocity;
            }
            if (e.key.code == sf::Keyboard::F5)
            {
                debugShowRadii = !debugShowRadii;
                Physics::plot(); // for testing
            }
        }

        m_p_application->debugInput(e);
    }

    void Playing::input()
    {
        ballPositions.clear();
        ballSpecies.clear();

        for(auto const& entity: m_entities)
            entity->input();
    }

    void Playing::update(double dt)
    {
        for(auto const& entity: m_entities)
            entity->update(dt);
    }

    void Playing::draw()
    {
        for(auto const& entity: m_entities)
        {
            entity->draw();
        }
    }

    void Playing::addBall(double x, double y)
    {
        m_entities.push_back(std::move(std::make_unique<Entities::Ball>(sf::Vector2<double>(x, y), 1, this)));
    }

    void Playing::populate(int numOfBalls)
    {
        for (int i = 0; i < numOfBalls; i++)
        {
            double x = BALL_RADIUS + Random::randomDouble() * (Display::WIDTH - 2 * BALL_RADIUS);
            double y = BALL_RADIUS + Random::randomDouble() * (Display::HEIGHT - 2 * BALL_RADIUS);
            addBall(x, y);
        }
    }

    void Playing::createSpecies(int num=1)
    {}

    void Playing::noticeBall(sf::Vector2<double> position, int spec)
    {
        ballPositions.push_back(position);
        ballSpecies.push_back(spec);
    }
}

