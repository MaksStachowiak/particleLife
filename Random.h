#pragma once

#include <SFML/Graphics.hpp>

namespace Random
{
    void init();

    double    randomDouble  ();
    int       random255     ();
    sf::Color randomColor   ();
    int randomRange         (int, int);
}