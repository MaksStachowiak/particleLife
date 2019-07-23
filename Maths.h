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

    // repulsion increases hyperbolically with distances smaller than diameter (overlap)
    // attraction increases linearly towards maxAttractionPoint, then decreases linearly towards zero
    sf::Vector2<double> getForce(sf::Vector2<double> a, sf::Vector2<double> b, double maxAttractionPoint)
    {
        double dist = distance(a, b);

        if (dist < 0.0001)
            return sf::Vector2<double>(0, 0);

        // if (dist > 2 * (maxAttractionPoint - BALL_RADIUS))
        //     return sf::Vector2<double>(0, 0);

        sf::Vector2<double> direction = normalise(b-a, dist);

        if (dist < 2*BALL_RADIUS)
        {
            direction *= BALL_RADIUS/dist;
            return direction;
        }
        // else
        // {
        //     direction *= -fabs(dist - maxAttractionPoint + 2*BALL_RADIUS)/10000;
        //     return direction;
        // }
        return sf::Vector2<double>(0, 0);
    }
}