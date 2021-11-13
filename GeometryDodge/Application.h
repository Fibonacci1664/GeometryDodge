#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>

class Application
{
public:
	Application();
	~Application();

	void run();

private:
	void initWindow();

	sf::RenderWindow window;
	
};

