#pragma once

#include <functional>

#include "StateBase.h"
#include "Entity.h"

struct speciesCharacteristics {int id; sf::Color color;};
struct interactionRules {double minRadius, maxRadius, maxMagnitude;};

namespace State
{
    class Playing : public StateBase
    {
        public:
            Playing (Application& application);

            void input      (const sf::Event& e);
            void input      ();
            void update     (double dt);
            void draw       ();
            void noticeBall (sf::Vector2<double>, int);

            std::vector<sf::Vector2<double>> ballPositions;
            std::vector<int> ballSpecies;

            int speciesNumber;

            std::vector<sf::Color> speciesColors;

            //for each species holds vector of their att/repulsion characteristics towards all other species
            std::vector<std::vector<interactionRules>> interactionCharacteristics;

            bool debugShowVelocity;
            bool debugShowRadii;

        private:
            void addBall(double, double);
            void populate(int);
            void createSpecies(int);

            std::vector<std::unique_ptr<Entities::Entity>> m_entities;
            
    };
}

