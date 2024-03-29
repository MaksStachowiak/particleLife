#include "Display.h"

#include "StateBase.h"

namespace Display
{
    namespace
    {
        sf::RenderWindow window;
        sf::Font font;
        // sf::Image icon;

        void checkForClose(const sf::Event& e)
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    void init(const std::string& name)
    {
        window.create({WIDTH, HEIGHT},
                       name,
                       sf::Style::Close);
        window.setVerticalSyncEnabled(true);
        font.loadFromFile("arial.ttf");
    }

    bool isOpen()
    {
        return window.isOpen();
    }

    void update()
    {
        window.display();
    }

    void clear (const sf::Color& colour)
    {
        window.clear(colour);
    }

    void draw(const sf::Drawable& drawable)
    {
        window.draw(drawable);
    }

    void pollEvents(State::StateBase& gameState)
    {
        sf::Event e;
        while (window.pollEvent(e))
        {
            gameState.input(e);
            checkForClose(e);
        }
    }

    const sf::RenderWindow& get()
    {
        return window;
    }

    sf::Font* getFont()
    {
        return &font;
    }

}