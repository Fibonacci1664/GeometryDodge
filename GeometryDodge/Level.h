#pragma once
#include "GameState.h"
#include "Screen.h"

class Level : public Screen
{
public:
	Level();
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:

	void beginDraw();
	void endDraw();
};

