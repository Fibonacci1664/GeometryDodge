#include "Application.h"


Application::Application()
{
	initWindow();
}

Application::~Application()
{
}

void Application::initWindow()
{
	window.create(sf::VideoMode(1280, 720), "Geometry Dodge!");
	window.setFramerateLimit(60);       // Diffrent OS may output slightly different FPS
}

void Application::run()
{
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }
}