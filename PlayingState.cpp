#include "PlayingState.h"

// #include "../Resource_Managers/Resource_Manager.h"
#include "Application.h"
#include "Display.h"

#include "Entity.h"
#include "Ball.h"

#include <iostream>

namespace State
{
    Playing::Playing(Application& application)
    : StateBase     (application)
    // ,   m_world     (m_player)
    {
        std::cout<<"Now playing"<<std::endl;
        // m_entities.push_back(std::move(std::make_unique<Entities::Ball>(sf::Vector2<double>(500, 300), 1, this)));
    }

    void Playing::input(const sf::Event& e)
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                addBall( static_cast <double> (e.mouseButton.x - BALL_RADIUS),
                         static_cast <double> (e.mouseButton.y - BALL_RADIUS) );
            }
        }
        if (e.type == sf::Event::KeyReleased)
        {
            if (e.key.code == sf::Keyboard::F3)
            {
                std::cout << m_entities.size() << std::endl;
            }
            if (e.key.code == sf::Keyboard::F4)
            {
                debugShowVelocity = !debugShowVelocity;
            }
        }

        m_p_application->debugInput(e);
    }

    void Playing::input()
    {
        positions.clear();
        species.clear();

        for(auto const& entity: m_entities)
            entity->input();
    }

    void Playing::update(float dt)
    {
        // m_entities.push_back(std::move(std::make_unique<Entities::Ball>(sf::Vector2<double>(500, 300), 1, this)));

        for(auto const& entity: m_entities)
            entity->update(dt);

        // m_notice.update();

        // switch(m_playerState)
        // {
        //     case Player_State::Roaming:
        //         roamUpdate(dt);
        //         break;

        //     case Player_State::Zone_Switch:
        //         zoneSwitchUpdate(dt);
        //         break;
        // }

        // if (m_player.getLevel().hasLeveledUp())
        // {
        //     m_player.heal();
        // }
    }

    void Playing::draw()
    {
        for(auto const& entity: m_entities)
        {
            entity->draw();
        }
//         switch(m_playerState)
//         {
//             case Player_State::Roaming:
//                 roamDraw();
//                 break;

//             case Player_State::Zone_Switch:
//                 zoneSwitchDraw();
//                 break;
//         }
//         m_notice.draw();
    }

    void Playing::addBall(double x, double y)
    {
        m_entities.push_back(std::move(std::make_unique<Entities::Ball>(sf::Vector2<double>(x, y), 1, this)));
    }

    void Playing::noticeBall(sf::Vector2<double> position, int spec)
    {
        positions.push_back(position);
        species.push_back(spec);
    }

//     void Playing::roamUpdate(float dt)
//     {
//        m_world.update (m_notice, dt);

//         if (m_player.getPosition().x >= Display::WIDTH  - 200 &&
//             m_player.getPosition().y <= 200)
//         {
//             m_notice.setString("Press space to interact!");
//             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//             {
//                 m_playerState = Player_State::Zone_Switch;
//                 m_mapGUI.resetBool();
//             }
//         }
//     }

//     void Playing::roamDraw()
//     {
//         m_world.draw ();
//     }

//     void Playing::zoneSwitchUpdate(float dt)
//     {
//         m_mapGUI.update(m_player, m_notice);
//         if (m_mapGUI.shouldExit())
//         {
//             if (m_mapGUI.getZoneID() != m_world.getZoneID())
//             {
//                 m_world.setZone(std::move(m_mapGUI.getZone()));
//             }
//             //get zone
//             //set zone
//             m_playerState = Player_State::Roaming;
//         }
//     }


//     void Playing::zoneSwitchDraw()
//     {
//         m_mapGUI.draw();
//     }
}