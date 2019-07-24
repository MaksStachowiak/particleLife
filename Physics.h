#pragma once

#include <SFML/Graphics.hpp>

namespace Physics
{
    sf::Vector2<double> getForce(sf::Vector2<double>, sf::Vector2<double>);
    void plot();
}