#pragma once

#include <cmath>

#include <SFML/Graphics.hpp>

namespace Maths
{
    double distance(double ax, double ay, double bx, double by)
    {
        return std::sqrt((ax - bx)*(ax - bx) + (ay - by)*(ay - by));  
    }

    double normalise(double x, double y)
    {
        double length = std::sqrt(x*x + y*y);
        return (x/length, y/length);
    }
}