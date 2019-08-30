#include "MenuState.h"

#include "Application.h"
#include "Display.h"
#include "Physics.h"

#include <iostream>
#include <fstream>


#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

namespace
{
    std::string exec(const char* cmd)
    {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            result += buffer.data();
        }
        return result;
    }
}

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
            if (e.key.code == sf::Keyboard::L) // load
            {
                std::string filename = exec("zenity --file-selection --file-filter=*.particlelife");
                std::cout << "opening " << filename << std::endl;
                filename = filename.substr(filename.find_last_of("/") + 1, filename.size()); // get relative path
                filename.erase(std::remove(filename.begin(), filename.end(), '\n'), filename.end()); // delete '\n'
                std::ifstream myfile(filename);
                std::string line;
                if (myfile.is_open())
                {
                    while ( getline (myfile,line) )
                    {
                    std::cout << line << '\n';
                    }
                    myfile.close();
                }
                else std::cout << "Unable to open file\n"; 
            }
            if (e.key.code == sf::Keyboard::S) // save
            {
                std::ofstream myfile;
                myfile.open ("example.particlelife");
                myfile << "Writing this to a file.\n";
                myfile.close();
            }
            if (e.key.code == sf::Keyboard::N) // new sim
            {
                m_p_application->newSimulation();
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
