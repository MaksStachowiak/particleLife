#pragma once

#include <SFML/Graphics.hpp>

#include "Physics.h"

class Species
{
    public:
        Species();

        sf::Color getColor();

    private:
        sf::Color m_color;
        double min_interaction_radius;
        double max_interaction_radius;
};