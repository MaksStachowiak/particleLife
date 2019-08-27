#include "PlayingState.h"

#include "Application.h"
#include "Display.h"
#include "Random.h"
#include "Physics.h"
#include "Message.h"

#include "Entity.h"
#include "Ball.h"

#include <iostream>

namespace State
{
    Playing::Playing(Application& application)
    : StateBase     (application)
    , speciesNumber     (0)
    , speciesSelection  (-1)
    , messagesToDelete  (0)
    , debugShowVelocity (false)
    , debugShowRadii    (false)
    , debugSpawnBalls   (false)
    {
        for (int i = 0; i < NUMBER_OF_SPECIES; i++)
            createSpecies();
        populate(STARTING_POPULATION);

        m_font.loadFromFile("arial.ttf"); 

        m_messages.clear();
        addMessage("Starting simulation with " + std::to_string(STARTING_POPULATION) + " particles");
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
                addBall( static_cast <double> (e.mouseButton.x - BALL_RADIUS),
                         static_cast <double> (e.mouseButton.y - BALL_RADIUS) );
        }
        if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::F3)
            {
                addMessage("Number of particles: " + std::to_string(m_entities.size()));
            }
            if (e.key.code == sf::Keyboard::F4)
            {
                debugShowVelocity = !debugShowVelocity;
                if (debugShowVelocity)
                    addMessage("Showing velocity vectors");
                else
                    addMessage("Hiding velocity vectors");
            }
            if (e.key.code == sf::Keyboard::F5)
            {
                debugShowRadii = !debugShowRadii;
                if (debugShowRadii)
                    addMessage("Showing radii of interaction");
                else
                    addMessage("Hiding radii of interaction");
                // Physics::plot(); // for testing
            }
            if (e.key.code == sf::Keyboard::F6)
            {
                debugSpawnBalls = false;
            }
            if (e.key.code == sf::Keyboard::F7)
            {
                if (speciesSelection < speciesNumber)
                {
                    speciesSelection++;
                    addMessage("New particles will be of type " + std::to_string(speciesSelection));
                }
                else
                {
                    speciesSelection = -1;
                    addMessage("New particles will be of random type");
                }
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
        
        for(auto const& message: m_messages)
            message->update(dt);
        for(int i = 0; i < messagesToDelete; i++)
            m_messages.pop_back();
        messagesToDelete = 0;
        
        if (debugSpawnBalls)
            addBall( static_cast <double> (sf::Mouse::getPosition(Display::get()).x - BALL_RADIUS),
                     static_cast <double> (sf::Mouse::getPosition(Display::get()).y - BALL_RADIUS) );
    }

    void Playing::draw()
    {
        for(auto const& entity: m_entities)
            entity->draw();

        if (speciesSelection >= 0)
        {
            sf::RectangleShape rectangle(sf::Vector2f(Display::WIDTH, 5));
            rectangle.setFillColor(speciesColors[speciesSelection]);
            rectangle.setPosition(0, 0);
            Display::draw(rectangle);
        }
        
        for(auto const& message: m_messages)
            message->draw();

    }

    void Playing::addBall(double x, double y)
    {
        int species = Random::randomRange(0, speciesNumber-1);
        if (speciesSelection >= 0)
            species = speciesSelection;
        m_entities.push_back(std::move(std::make_unique<Entities::Ball>(sf::Vector2<double>(x, y), species, speciesColors[species], this)));
        addMessage("New particle of species " + std::to_string(species));// + " at " + std::to_string(static_cast<int>(x)) + ", " + std::to_string(static_cast<int>(y)));
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

    int Playing::getSpeciesNumber()
    {
        return speciesNumber;
    }
    
    int Playing::getSpeciesSelection()
    {
        return speciesSelection;
    }

    void Playing::noticeBall(sf::Vector2<double> position, int spec)
    {
        ballPositions.push_back(position);
        ballSpecies.push_back(spec);
    }

    void Playing::addMessage(std::string text_string)
    {
        for(auto const& message: m_messages)
            message->pushDown();
        m_messages.push_front(std::move(std::make_unique<Entities::Message>(text_string, 0, this)));
    }
}