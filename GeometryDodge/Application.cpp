#include "Application.h"
#include <iostream>


Application::Application(int width, int height) : windowWidth(width), windowHeight(height)
{
	initWindow();
}

Application::~Application()
{
    /*if (gameState)
    {
        delete gameState;
        gameState = nullptr;
    }*/

    if (level)
    {
        delete level;
        level = nullptr;
    }
}

void Application::initWindow()
{
	window.create(sf::VideoMode(windowWidth, windowHeight), "Asteroid Dodge!");
    // NEVER have both vSync AND framerate limit, it's either or, NEVER both!
    // If you find vSync is having no effect, check graphics driver's settings and change vSync from "off" to "controlled by application"
    //window.setVerticalSyncEnabled(true);    // Ensure the application runs at the same frequency as the monitor's refresh rate
    window.setFramerateLimit(60);           // Request a fixed framerate, diffrent OS may output slightly different FPS

    // Get the native screen res
    int nativeScreenWidth = sf::VideoMode::getDesktopMode().width;
    int nativeScreenHeight = sf::VideoMode::getDesktopMode().height;

    // Place the viewing window in the centre of the screen
    window.setPosition(sf::Vector2i((nativeScreenWidth * 0.5f) - (windowWidth * 0.5f), (nativeScreenHeight * 0.5f) - (windowHeight * 0.5f)));
}

void Application::run()
{
    gameState.setCurrentState(State::LEVEL);

    sf::Clock clock;
    float deltaTime;
    float sendRate = 0.05f;
    float latency = 0.3f;		// Simulated latency
    float gameSpeed = 1.0f;
    float startTime = sendRate * 3.0f;

    //When are we next printing the predicted position (so we don't spam the console)
    float nextPrint = startTime;

    //Create a network simulator with that "sends" a message every 0.5 seconds and has a latency of 0.3 seconds
    NetworkSimulator netSimulator(sendRate, latency);
    netSimulator.m_MyID = 0;	// On the network, we are Player 0

    // Run the program as long as the window is open
    while (window.isOpen())
    {
        level = new Level(&window, &input, &gameState);
        float deltaTime;

        // If the game isn't over, keep processing stuff
        while (gameState.getCurrentState() != State::GAMEOVER)
        {
            processWindowEvents(&netSimulator, nextPrint, startTime);
            
            // Calculate delta time. How much time has passed 
            // since it was last calculated (in seconds) and restart the clock.
            deltaTime = clock.restart().asSeconds();

            //If we're at the start, just advance the time by 1.5 seconds, so we have a few packets in the queue already
            if (netSimulator.Time() < 1.0f)
            {
                std::cout << "BEGIN SIMULATION\n";

                printf("BEGIN SIMULATION\n");
                netSimulator.Update(startTime, sf::Vector2f(0, 0));
            }

            switch (gameState.getCurrentState())
            {
                case(State::LEVEL):
                {
                    level->handleInput(deltaTime);
                    level->update(deltaTime, &netSimulator, nextPrint, sendRate);
                    level->render();
                    break;
                }
                case(State::GAMEOVER):
                {
                    break;
                }
                case(State::PAUSE):
                {
                    /* pause->handleInput(deltaTime);
                     pause->update(deltaTime);
                     pause->render();
                     break;*/
                }
            }

            //switchGameState(level, deltaTime);
        }

        // Destroy all old game objects, except gameState
        break;

        // Set game back to main menu
        //gameState->setCurrentState(State::MENU);
    }
}

void Application::processWindowEvents(NetworkSimulator* netSim, float& nextPrint, float& startTime)//, Input* in)
{
    // Check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    unsigned int n_buts = 0;
    //window.setJoystickThreshold(2.0f);        // This doesn't do anything, threshold is controlled in Input class

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }
            case sf::Event::Resized:
            {
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
                break;
            }
            case sf::Event::LostFocus:
            {
                // Pause game if window loses focus
            }
            case sf::Event::GainedFocus:
            {
                // Resume game when window gains focus again
            }
            case sf::Event::JoystickConnected:
            {
                std::cout << "Controller is connected!.\n";
                n_buts = sf::Joystick::getButtonCount(0);
                std::cout << "joystick zero button count = " << n_buts << '\n';

                if (sf::Joystick::hasAxis(0, sf::Joystick::X))
                {
                    std::cout << "supports x-axis movement\n";
                }

                if (sf::Joystick::hasAxis(0, sf::Joystick::Y))
                {
                    std::cout << "supports y-axis movement\n";
                }

                break;
            }
            case sf::Event::JoystickDisconnected:
            {
                std::cout << "Controller is disconnected!.\n";
                break;
            }
            case sf::Event::JoystickMoved:
            {
                // Need an input class that handles input
                input.setLeftStick(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
            }
            case sf::Event::JoystickButtonPressed:
            {
                // Need an input class that handles input
            }
            case sf::Event::JoystickButtonReleased:
            {
                // Need an input class that handles input
            }
            case sf::Event::KeyPressed:
            {
                if (event.key.code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }

                if (event.key.code == sf::Keyboard::Key::R)
                {
                    level->reset();
                    netSim->Reset();
                    nextPrint = startTime;
                    printf("\n\n--------RESET--------\n\n");
                }
            }
            case sf::Event::KeyReleased:
            {
                // Need an input class that handles input
            }
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //update input class
                    //in->setMouseLDown(true);
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    //update input class
                    //in->setMouseLDown(false);
                }
                break;
            }
        }
    }
}

//void Application::switchGameState(Level* level, float deltaTime)
//{
//    switch (gameState.getCurrentState())
//    {
//        //case(State::MENU):
//        //{
//        //    menu->handleInput(deltaTime);
//        //    menu->update(deltaTime);
//        //    menu->render();
//        //    break;
//        //}
//        //case(State::HOW_TO_PLAY):
//        //{
//        //    /*howToPlay->handleInput(deltaTime);
//        //    howToPlay->update(deltaTime);
//        //    howToPlay->render();
//        //    break;*/
//        //}
//        case(State::LEVEL):
//        {
//            level->handleInput(deltaTime);
//            level->update(deltaTime);
//            level->render();
//            break;
//        }
//        case(State::GAMEOVER):
//        {
//            break;
//        }
//        case(State::PAUSE):
//        {
//           /* pause->handleInput(deltaTime);
//            pause->update(deltaTime);
//            pause->render();
//            break;*/
//        }
//    }
//}