#include "Random.h"

#include <cstdlib>
#include <ctime>

namespace Random
{
    void init()
    {
        std::srand(std::time(nullptr));
    }

    //uniform on 0.0:1.0
    double randomDouble()
    {
        return static_cast <double> (std::rand()) / static_cast <double> (RAND_MAX);
    }

    //uniform on 1:255 inclusive
    int random255()
    {
        int x = 256;
        while(x > 255)
            x = 1 + std::rand()/((RAND_MAX + 1u)/255);
        return x;
    }

    sf::Color randomColor()
    {
        return sf::Color(random255(),random255(),random255());
    }
}