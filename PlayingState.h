#pragma once

#include <functional>

#include "StateBase.h"
#include "Entity.h"

namespace State
{
    class Playing : public StateBase
    {
        public:
            Playing (Application& application);

            void input      (const sf::Event& e);
            void input      ();
            void update     (float dt);
            void draw       ();
            void noticeBall (sf::Vector2<double>, int);

            std::vector<sf::Vector2<double>> positions;
            std::vector<int> species;

        private:
            void addBall(double, double);

            std::vector<std::unique_ptr<Entities::Entity>> m_entities;
    };
}
