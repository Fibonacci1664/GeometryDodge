#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs) : Screen(hwnd, in, gs)
{
	initLevel();
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

	checkCurrentWave();

	// Update all the asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i]->update(dt);
	}
}

void Level::render()
{
	beginDraw();

	// Render stuff here
	window->draw(bgSprite);
	window->draw(*ui->getWaveText());
	window->draw(*ui->getCountdownText());
	window->draw(*player1->getPlayerSprite());

	// Draw all the asteroids
	for (int i = 0; i < asteroids.size(); i++)
	{
		window->draw(*asteroids[i]->getAsteroidSprite());
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