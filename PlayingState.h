#pragma once

#include <functional>
#include <list>

#include "StateBase.h"
#include "Entity.h"
#include "Message.h"
#include "Physics.h"

namespace State
{
    class Playing : public StateBase
    {
        public:
            Playing (Application& application);
            Playing (Application& application, std::vector<std::vector<Physics::interactionRules>>, std::vector<sf::Color>);

            void input      (const sf::Event& e);
            void input      ();
            void update     (double dt);
            void draw       ();

            void noticeBall (sf::Vector2<double>, int);
            void noticeMessageDeath();

            int getSpeciesNumber();
            int getSpeciesSelection();

            std::vector<sf::Vector2<double>> ballPositions;
            std::vector<int> ballSpecies;
            std::vector<sf::Color> speciesColors;

            //for each species holds vector of their att/repulsion characteristics towards all other species
            std::vector<std::vector<Physics::interactionRules>> interactionCharacteristics;

            int messagesToDelete;

            bool debugShowVelocity;
            bool debugShowRadii;
            bool debugSpawnBalls;

        private:
            void addMessage(std::string);
            void addBall(double, double);
            void populate(int);
            void createSpecies();

            int speciesNumber;
            int speciesSelection;

            sf::Font m_font;

            std::list<std::unique_ptr<Entities::Message>> m_messages;
            std::vector<std::unique_ptr<Entities::Entity>> m_entities;

    };
}

