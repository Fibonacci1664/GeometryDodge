#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include "GameState.h"
#include "Level.h"
#include "NetworkSimulator.h"

class Application
{
public:
	Application(int width, int height);
	~Application();

	void run();

private:
	void initWindow();
	void processWindowEvents(NetworkSimulator* netSim, float& nextPrint, float& startTime);
	void switchGameState(Level* level, float deltaTime);

	sf::RenderWindow window;
	Input input;
	GameState gameState;
	Level* level;

	int windowWidth;
	int windowHeight;
	
};

