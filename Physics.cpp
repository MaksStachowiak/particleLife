#include "Physics.h"

#include <iostream>

#include "Maths.h"
#include "Random.h"
#include "Application.h"

namespace Physics
{
    sf::Vector2<double> getForce(sf::Vector2<double> a, sf::Vector2<double> b, interactionRules i)
    {
        double slope  = 2 * i.maxMagnitude / (i.maxRadius - i.minRadius);
        double center = (i.maxRadius + i.minRadius) / 2;
        double dist   = Maths::distance(a, b);

        //if interacting with self then ignore
        if (dist < 0.000001)
            return sf::Vector2<double>(0, 0);
        
        //get unit vector in the direction of particle
        auto result = Maths::normalise(b-a, dist);

        // repulsion increases hyperbolically with distances smaller than diameter (overlap)
        if (dist < i.minRadius)
        {
            result *= BALL_DIAM/(dist+1)-1;
            return result;
        }
        // interaction force increases linearly towards maxMagnitude, then decreases linearly towards zero
        else if (dist < i.maxRadius)
        {
            result *= i.maxMagnitude - slope * fabs(dist - center);
            return result;
        }
        return sf::Vector2<double>(0, 0);
    }
    
    Physics::interactionRules newInteraction()
    {
        Physics::interactionRules iR = Physics::interactionRules();
        iR.minRadius = BALL_RADIUS * (1 + MIN_RADIUS_MULTIPLIER * Random::randomDouble());
        iR.maxRadius = iR.minRadius + BALL_RADIUS * (1 + MAX_RADIUS_MULTIPLIER * Random::randomDouble());
        iR.maxMagnitude = (Random::randomDouble() - 0.5) * INTERACTION_FORCE_MULTIPLIER;
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
