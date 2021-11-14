#pragma once
#include "GameState.h"
#include "Screen.h"
#include "Player.h"
#include "UI.h"

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
	void initBackground();
	void initUI();
	void initLevel();
	void initPlayer();
	void beginDraw();
	void endDraw();
	void loadTexture();

	UI* ui;
	Player* player1;
	//Player player2;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
};

