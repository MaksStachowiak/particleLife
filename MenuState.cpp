#include "MenuState.h"

#include "Application.h"
#include "Display.h"
#include "Physics.h"

#include <iostream>

namespace State
{
    Menu::Menu(Application& application)
    : StateBase     (application)
    {
    }
    
    Menu::Menu(Application& application, std::vector<std::vector<Physics::interactionRules>> rules, std::vector<sf::Color> colors)
    : StateBase     (application)
    , currentRules  (rules)
    , currentColors (colors)
    {
    }

    void Menu::input(const sf::Event& e)
    {
        if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::Escape)
            {
                m_p_application->closeMenu();
            }
            if (e.key.code == sf::Keyboard::R) // reset
            {
                m_p_application->newSimulation(currentRules, currentColors);
            }
        }    
    }

    void Menu::input()
    {
    }

    void Menu::update(double dt)
    {
    }

    void Menu::draw()
    {
        sf::RectangleShape rectangle(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color(200, 0, 0));
        rectangle.setPosition(100, 100);
        Display::draw(rectangle);
    }

}
