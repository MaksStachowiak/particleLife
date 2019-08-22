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
    , speciesSelection  (-1)
    , debugShowVelocity (false)
    , debugShowRadii    (false)
    , debugSpawnBalls   (false)
    {
        for (int i = 0; i < NUMBER_OF_SPECIES; i++)
            createSpecies();
        populate(STARTING_POPULATION);
        std::cout<<"Now playing"<<std::endl;
    }

    void Playing::input(const sf::Event& e)
    {
        if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::F6)
            {
                debugSpawnBalls = true;
            }
        }
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
            if (e.key.code == sf::Keyboard::F6)
            {
                debugSpawnBalls = false;
            }
            if (e.key.code == sf::Keyboard::F7)
            {
                if (speciesSelection < speciesNumber)
                    speciesSelection++;
                else
                    speciesSelection = -1;
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

        if (debugSpawnBalls)
            addBall( static_cast <double> (sf::Mouse::getPosition(Display::get()).x - BALL_RADIUS),
                     static_cast <double> (sf::Mouse::getPosition(Display::get()).y - BALL_RADIUS) );
    }

    void Playing::draw()
    {
        for(auto const& entity: m_entities)
        {
            entity->draw();
        }

        if (speciesSelection >= 0)
        {
            sf::RectangleShape rectangle(sf::Vector2f(Display::WIDTH, 5));
            rectangle.setFillColor(speciesColors[speciesSelection]);
            rectangle.setPosition(0, 0);
            Display::draw(rectangle);
        }
 
    }

    void Playing::addBall(double x, double y)
    {
        int species = Random::randomRange(0, speciesNumber-1);
        if (speciesSelection >= 0)
            species = speciesSelection;
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
        speciesColors.push_back(Random::randomColor());
        // add new interaction to all existing species'
        if (speciesNumber > 0)
            for (auto&& i : interactionCharacteristics)
                i.push_back(Physics::newInteraction());
        // create new species
        interactionCharacteristics.push_back(std::vector<Physics::interactionRules>());
        speciesNumber++;
        // for every species create interactions between new and existing
        for (auto i : interactionCharacteristics)
            interactionCharacteristics[speciesNumber-1].push_back(Physics::newInteraction());
    }

    void Playing::noticeBall(sf::Vector2<double> position, int spec)
    {
        ballPositions.push_back(position);
        ballSpecies.push_back(spec);
    }
}