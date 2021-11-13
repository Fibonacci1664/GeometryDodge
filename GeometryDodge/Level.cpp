#include "Level.h"

Level::Level()
{

}

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs) : Screen(hwnd, in, gs)
{

}

Level::~Level()
{

}

void Level::handleInput(float dt)
{

}

void Level::update(float dt)
{

}

void Level::render()
{
	beginDraw();

	// Render stuff here

	endDraw();
}

void Level::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

void Level::endDraw()
{
	window->display();
}