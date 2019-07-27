#include "Physics.h"

#include <iostream>

#include "Maths.h"
#include "Random.h"
#include "Application.h"

namespace Physics
{
    sf::Vector2<double> getForce(sf::Vector2<double> a, sf::Vector2<double> b, interactionRules i)
    {
        double min_dist = i.minRadius;
        double max_dist = i.maxRadius;
        double magnitude = i.maxMagnitude;

        double slope = 2*magnitude/(max_dist - min_dist);
        double center = (max_dist + min_dist)/2;

        double dist = Maths::distance(a, b);

        //if interacting with self then ignore
        if (dist < 0.000001)
            return sf::Vector2<double>(0, 0);
        
        //get unit vector in direction of particle
        auto result = Maths::normalise(b-a, dist);

        // repulsion increases hyperbolically with distances smaller than diameter (overlap)
        if (dist < min_dist)
        {
            result *= BALL_DIAM/(dist+1)-1;
            return result;
        }
        // attraction/repulsion increases linearly towards maxAttractionPoint, then decreases linearly towards zero
        else if (dist < max_dist)
        {
            result *= magnitude - slope * fabs(dist - center);
            return result;
        }
        return sf::Vector2<double>(0, 0);
    }
    
    Physics::interactionRules newInteraction()
    {
        Physics::interactionRules iR = Physics::interactionRules();
        iR.minRadius = BALL_RADIUS * (1 + 5 * Random::randomDouble());
        iR.maxRadius = iR.minRadius + BALL_RADIUS * (1 + 10 * Random::randomDouble());
        iR.maxMagnitude = (Random::randomDouble() - 0.5) * 0.8;
        return iR;
    }

    void plot(interactionRules iR)
    {
        for (int i = 1; i<1000; i++)
        {
            double increment = i*BALL_RADIUS*0.02;
            std::cout << increment << " " << getForce(sf::Vector2<double>(0, 0), sf::Vector2<double>(increment, 0), iR).x << std::endl;
        }
    }
}
