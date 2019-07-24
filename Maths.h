#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

namespace Maths
{
    double distance(sf::Vector2<double> a, sf::Vector2<double> b)
    {
        return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));  
    }

    sf::Vector2<double> normalise(sf::Vector2<double> x, double length)
    {
        x /= length;
        return x;
    }
}