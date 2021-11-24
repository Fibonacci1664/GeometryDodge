#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs) : Screen(hwnd, in, gs)
{
	isDebugMode = true;

	initLevel();

	if (isDebugMode)
	{
		initDebugMode();
	}
}

Level::~Level()
{
	if (player1)
	{
		delete player1;
		player1 = nullptr;
	}

	if (ui)
	{
		delete ui;
		ui = nullptr;
	}

	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (asteroids[i])
		{
			delete asteroids[i];
			asteroids[i] = nullptr;
		}
	}
}

void Level::initLevel()
{
	initBackground();
	initUI();
	initPlayer();
	initAsteroids();
}

void Level::initDebugMode()
{
	// Player debug collision box
	playerColBox.setFillColor(sf::Color(0, 0, 0, 0));
	playerColBox.setOutlineColor(sf::Color::Magenta);
	playerColBox.setOutlineThickness(1.0f);

	// Set the collision box origin to be the top left of the sprites local coords, this is
	// based on the already defined collision box which was defined during object creation
	playerColBox.setPosition(sf::Vector2f(player1->getCollisionBox().left, player1->getCollisionBox().top));
	playerColBox.setSize(sf::Vector2f(player1->getCollisionBox().width, player1->getCollisionBox().height));

	// Create a new asteroid collision box
	asteroidColBoxes.push_back(sf::RectangleShape());

	// Asteroids debug collision boxes
	asteroidColBoxes[0].setFillColor(sf::Color(0, 0, 0, 0));
	asteroidColBoxes[0].setOutlineColor(sf::Color::Magenta);
	asteroidColBoxes[0].setOutlineThickness(1.0f);

	// Set the collision box origin to be the top left of the sprites local coords, this is
	// based on the already defined collision box which was defined during object creation
	asteroidColBoxes[0].setPosition(sf::Vector2f(asteroids[0]->getCollisionBox().left, asteroids[0]->getCollisionBox().top));
	asteroidColBoxes[0].setSize(sf::Vector2f(asteroids[0]->getCollisionBox().width, asteroids[0]->getCollisionBox().height));
}

void Level::initBackground()
{
	loadTexture();
	bgTexture.setSmooth(true);
	bgSprite.setTexture(bgTexture);
	//bgSprite.setOrigin(bgSprite.getTextureRect().width * 0.5f, bgSprite.getTextureRect().height * 0.5f);
	////bgSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	bgSprite.setScale(5.0f, 2.8125f);
}

void Level::initUI()
{
	ui = new UI;
	currentWave = ui->getWaveCount();
}

void Level::initPlayer()
{
	player1 = new Player(1, window, input);
}

void Level::initAsteroids()
{
	asteroids.push_back(new Asteroid(window));
}

void Level::spawnNewAsteroid()
{
	// If we get here it means the wave count was incremented, so spawn an asteroid
	asteroids.push_back(new Asteroid(window));
	createNewAsteroidColBox();
}

void Level::checkCurrentWave()
{
	if (currentWave != ui->getWaveCount())
	{
		spawnNewAsteroid();
		currentWave = ui->getWaveCount();
	}
}

void Level::handleInput(float dt)
{
	player1->handleInput(dt);
}

void Level::update(float dt)
{
	ui->update(dt);
	player1->update(dt);

	if (isDebugMode)
	{
		// Update the players collision box
		playerColBox.setPosition(sf::Vector2f(player1->getCollisionBox().left, player1->getCollisionBox().top));

		// Update all the asteroids collision boxes
		for (int i = 0; i < asteroidColBoxes.size(); ++i)
		{
			asteroidColBoxes[i].setPosition(sf::Vector2f(asteroids[i]->getCollisionBox().left, asteroids[i]->getCollisionBox().top));
		}
	}

	checkCurrentWave();

	// Update all the asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->update(dt);
	}

	checkCollisions();
}

void Level::render()
{
	beginDraw();

	// Render stuff here
	window->draw(bgSprite);
	window->draw(*ui->getWaveText());
	window->draw(*ui->getCountdownText());

	// Draw all the asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		window->draw(*asteroids[i]->getAsteroidSprite());
	}

	window->draw(*player1->getPlayerSprite());

	// Draw all the debug magenta collision boxes
	if (isDebugMode)
	{
		window->draw(playerColBox);

		for (int i = 0; i < asteroidColBoxes.size(); ++i)
		{
			window->draw(asteroidColBoxes[i]);
		}
	}

	endDraw();
}

void Level::beginDraw()
{
	window->clear(sf::Color::Black);
}

void Level::endDraw()
{
	window->display();
}

void Level::loadTexture()
{
	if (!bgTexture.loadFromFile("res/gfx/bg/blue.png"))
	{
		std::cout << "Error loading background texture.\n";
	}
}

void Level::checkCollisions()
{
	// If player collides with an asteroid, set GAME_OVER state
	for (int i = 0; i < asteroids.size(); ++i)
	{
		if (player1->getCollisionBox().intersects(asteroids[i]->getCollisionBox()))
		{
			gameState->setCurrentState(State::GAMEOVER);
		}
	}
}

void Level::createNewAsteroidColBox()
{
	// Create a new asteroid collision box
	asteroidColBoxes.push_back(sf::RectangleShape());

	// Access the last element in the vector, i.e. the one we just pushed back
	int index = asteroidColBoxes.size() - 1;

	asteroidColBoxes[index].setFillColor(sf::Color(0, 0, 0, 0));
	asteroidColBoxes[index].setOutlineColor(sf::Color::Magenta);
	asteroidColBoxes[index].setOutlineThickness(1.0f);

	// Set the collision box origin to be the top left of the sprites local coords, this is
	// based on the already defined collision box which was defined during object creation
	asteroidColBoxes[index].setPosition(sf::Vector2f(asteroids[index]->getCollisionBox().left, asteroids[index]->getCollisionBox().top));
	asteroidColBoxes[index].setSize(sf::Vector2f(asteroids[index]->getCollisionBox().width, asteroids[index]->getCollisionBox().height));
}