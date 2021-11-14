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
}

void Level::initLevel()
{
	initUI();
	initPlayer();
}

void Level::initUI()
{
	ui = new UI;
}

void Level::initPlayer()
{
	player1 = new Player(1);
}

void Level::handleInput(float dt)
{
	player1->handleInput(dt);
}

void Level::update(float dt)
{
	ui->update(dt);
	player1->update(dt);
}

void Level::render()
{
	beginDraw();

	// Render stuff here
	window->draw(*player1->getPlayerSprite());
	window->draw(*ui->getWaveText());
	window->draw(*ui->getCountdownText());

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