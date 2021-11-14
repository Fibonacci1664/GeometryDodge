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
	initBackground();
	initUI();
	initPlayer();
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
}

void Level::initPlayer()
{
	player1 = new Player(1);
	player1->setInput(input);
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
	window->draw(bgSprite);
	window->draw(*ui->getWaveText());
	window->draw(*ui->getCountdownText());
	window->draw(*player1->getPlayerSprite());
	
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