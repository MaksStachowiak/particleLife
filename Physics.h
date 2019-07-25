#pragma once

#include <SFML/Graphics.hpp>


namespace Physics
{
    
    struct interactionRules {double minRadius, maxRadius, maxMagnitude;};

    sf::Vector2<double> getForce(sf::Vector2<double>, sf::Vector2<double>, interactionRules);
    void plot();
}