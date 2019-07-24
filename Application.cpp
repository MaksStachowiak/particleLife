#include "Application.h"

#include <iostream>

#include "Display.h"
#include "Random.h"

#include "PlayingState.h"

// #include "Game/Equipment/Equipment_Data.h"

namespace
{
    void calculateFPS(bool debugFPS)
    {
        static sf::Clock timer;
        static sf::Clock printTimer;
        static auto numFrames = 0;

        numFrames++;

        if (printTimer.getElapsedTime().asSeconds() >= 1.0f)
        {
            auto fps = (double)numFrames / timer.getElapsedTime().asSeconds();
            printTimer.restart();
            if (debugFPS)
                std::cout << fps << std::endl;

            numFrames = 0;
            timer.restart();
        }
    }
}

Application::Application()
: debugMousePos (false)
, debugFPS      (false)
{
    Display ::init  ("particleLife 0.3");
    Random  ::init  ();

    // m_music.setLoop(true);
    // m_music.openFromFile("Res/Music/cs8b.ogg");
    // m_music.setVolume(10);
    // m_music.play();

    // pushState(std::make_unique<State::Splash_Screen>(*this));
    pushState(std::make_unique<State::Playing>(*this));
}

void Application::runMainLoop()
{
    sf::Clock c;
    while (Display::isOpen())
    {
        auto dt = c.restart().asSeconds();

        Display::clear({0, 0, 0});
        
        m_states.top()->input   ();
        m_states.top()->update  (dt);
        m_states.top()->draw    ();

        Display::update         ();
        calculateFPS            (debugFPS);

        Display::pollEvents(*m_states.top());

        debugUpdate();
    }
}

void Application::debugInput(const sf::Event& e)
{
    if (e.type == sf::Event::KeyReleased)
    {
        if (e.key.code == sf::Keyboard::F1)
        {
            debugMousePos = !debugMousePos;
        }
        if (e.key.code == sf::Keyboard::F2)
        {
            debugFPS = !debugFPS;
        }
    }
}

void Application::debugUpdate()
{
    if (debugMousePos)
        {
            std::cout << " X: " << sf::Mouse::getPosition(Display::get()).x
                      << " Y: " << sf::Mouse::getPosition(Display::get()).y
                      << std::endl;
        }
}

void Application::pushState(std::unique_ptr<State::StateBase> state)
{
    m_states.push(std::move(state));
}

void Application::popState()
{
    m_states.pop();
}