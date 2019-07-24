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
        double dist = Maths::distance(a, b);

        //if interacting with self then ignore
        if (dist < 0.0001)
            return sf::Vector2<double>(0, 0);
        
        //get unit vector in direction of particle
        auto result = Maths::normalise(b-a, dist);

        if (dist < BALL_DIAM)
        {
            result *= BALL_RADIUS/(dist+0.0001);
            return result;
        }
        else
        {
            result *= fabs(dist-BALL_DIAM);
        }

        return sf::Vector2<double>(0, 0);
    }

    void plot()
    {
        for (int i = 1; i<100; i++)
        {
            double increment = i*BALL_RADIUS*0.2;
            std::cout << increment << " " << getForce(sf::Vector2<double>(0, 0), sf::Vector2<double>(increment, 0)).x << std::endl;
        }
    }
}
