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
    , speciesNumber     (0)
    , debugShowVelocity (false)
    , debugShowRadii    (false)
    {
        createSpecies();
        createSpecies();
        createSpecies();
        createSpecies();
        createSpecies();
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
                // Physics::plot(); // for testing
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
        int species = Random::randomRange(0, speciesNumber-1);
        m_entities.push_back(std::move(std::make_unique<Entities::Ball>(sf::Vector2<double>(x, y), species, speciesColors[species], this)));
    }

    void Playing::populate(int numOfBalls)
    {
        for (int i = 0; i < numOfBalls; i++)
        {
            double x = BALL_RADIUS + Random::randomDouble() * (Display::WIDTH - BALL_DIAM);
            double y = BALL_RADIUS + Random::randomDouble() * (Display::HEIGHT - BALL_DIAM);
            addBall(x, y);
        }
    }

    void Playing::createSpecies()
    {
        std::cout << "creating new species color" << std::endl;
        speciesColors.push_back(Random::randomColor());
        if (speciesNumber > 0)
            for (int i = 0; i < speciesNumber; i++)
            {
                std::cout << "adding new interactions to existing species " << i << std::endl;
                interactionCharacteristics[i].push_back(newInteraction());
            }
        std::cout << "creating new interactions class" << std::endl;
        interactionCharacteristics.push_back(std::vector<Physics::interactionRules>());
        speciesNumber++;
        for (int i = 0; i <= speciesNumber; i++)
        {
            std::cout << "adding new interaction " << i <<  " to last species " << speciesNumber - i << std::endl;
            std::cout << interactionCharacteristics[speciesNumber-1].size() << std::endl;
            Physics::interactionRules newRules = newInteraction();
            std::cout << "newRules.maxMagnitude " << newRules.maxMagnitude << std::endl;
            interactionCharacteristics[speciesNumber-1].push_back(newRules);
            std::cout << interactionCharacteristics[speciesNumber-1].size() << std::endl;
            std::cout << "added" << std::endl;
            std::cout << interactionCharacteristics[speciesNumber-1][i].maxMagnitude << std::endl;
        }
    }

    Physics::interactionRules Playing::newInteraction()
    {
        Physics::interactionRules i = Physics::interactionRules();
        i.minRadius = BALL_RADIUS * (1 + 3 * Random::randomDouble());
        i.maxRadius = i.minRadius + BALL_RADIUS * (1 + 3 * Random::randomDouble());
        i.maxMagnitude = Random::randomDouble() - 0.5;
        std::cout << "new interaction with i.maxMagnitude " << i.maxMagnitude << std::endl;
        std::cout << "new interaction with i.minRadius " << i.minRadius << std::endl;
        std::cout << "new interaction with i.maxRadius " << i.maxRadius << std::endl;
        return i;
    }

    void Playing::noticeBall(sf::Vector2<double> position, int spec)
    {
        ballPositions.push_back(position);
        ballSpecies.push_back(spec);
    }
}

