#include "Ball.h"

#include "Application.h"
#include "Display.h"

#include <iostream>

namespace Entities
{
    Ball::Ball()
    : Entity()
    { std::cout << "New ball!" << std::endl; }

    void Ball::input  (const sf::Event& e)
    { }
    void Ball::input  ()
    { }
    void Ball::update (float dt)
    { }
    void Ball::draw   ()
    { }
}