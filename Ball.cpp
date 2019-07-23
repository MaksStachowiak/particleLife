#include "Ball.h"

#include "Application.h"
#include "Display.h"

#include <iostream>

namespace Entities
{
    Ball::Ball(int x, int y)
    : Entity()
    , posX (x)
    , posY (y)
    {
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
        circle.setFillColor(sf::Color(100, 250, 50));
        circle.setPosition(posX, posY);
        Display::draw(circle);
    }
}