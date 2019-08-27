#pragma once

#include <cstdint>
#include <SFML/Graphics.hpp>

#include "Config.h"

namespace State
{
    class StateBase;
}

namespace Display
{
    void init   (const std::string& name = "Window");

    bool isOpen ();

    void update ();
    void clear  (const sf::Color& colour = {0, 0, 0});

    void draw(const sf::Drawable& drawable);

    void pollEvents(State::StateBase& gameState);

    const sf::RenderWindow& get();

    sf::Font* getFont();

}