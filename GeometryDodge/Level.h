#pragma once
#include "GameState.h"
#include "Screen.h"
#include "Player.h"

class Level : public Screen
{
public:
	Level() {}
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render() override;

private:
	void initPlayer();
	void beginDraw();
	void endDraw();

	Player* player1;
	//Player player2;
};

