#include "Ball.h"

#include "Application.h"
#include "Display.h"
#include "Random.h"

#include <iostream>

namespace Entities
{
    Ball::Ball(double x, double y)
    : Entity()
    , posX (x)
    , posY (y)
    {
        color = Random::randomColor();
        std::cout << "New ball!" << std::endl;
    }

    void Ball::input  (const sf::Event& e)
    { }
    void Ball::input  ()
    { }
    void Ball::update (float dt)
    { }
    void Ball::draw   ()
    {
        sf::CircleShape circle(BALL_RADIUS);
        circle.setFillColor(color);
        circle.setPosition(posX, posY);
        Display::draw(circle);
    }
}