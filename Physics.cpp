#include "Physics.h"

#include <iostream>

#include "Maths.h"
#include "Application.h"

namespace Physics
{
    // repulsion increases hyperbolically with distances smaller than diameter (overlap)
    // attraction increases linearly towards maxAttractionPoint, then decreases linearly towards zero

    sf::Vector2<double> getForce(sf::Vector2<double> a, sf::Vector2<double> b) //, interactionRulse i)
    {
        double min_dist = BALL_RADIUS * 2;
        double max_dist = BALL_RADIUS * 8;
        double magnitude = -0.5;

        double slope = 2*magnitude/(max_dist - min_dist);
        double center = (max_dist + min_dist)/2;

        double dist = Maths::distance(a, b);

        //if interacting with self then ignore
        if (dist < 0.000001)
            return sf::Vector2<double>(0, 0);
        
        //get unit vector in direction of particle
        auto result = Maths::normalise(b-a, dist);

        if (dist < min_dist)
        {
            result *= BALL_DIAM/(dist+1)-1;
            return result;
        }
        else if (dist < max_dist)
        {
            result *= magnitude - slope * fabs(dist - center);
            return result;
        }
        return sf::Vector2<double>(0, 0);
    }

    void plot()
    {
        for (int i = 1; i<1000; i++)
        {
            double increment = i*BALL_RADIUS*0.02;
            std::cout << increment << " " << getForce(sf::Vector2<double>(0, 0), sf::Vector2<double>(increment, 0)).x << std::endl;
        }
    }
}
