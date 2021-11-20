#pragma once
#include "GameState.h"
#include "Screen.h"
#include "Player.h"
#include "UI.h"
#include "Asteroid.h"
#include "NetworkSimulator.h"

class Level : public Screen
{
public:
	Level() {}
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs);
	~Level();

	void handleInput(float dt) override;
	void update(float dt, NetworkSimulator* netSimulator, float nextPrint, float sendRate) override;
	void render() override;
	void reset();

private:
	void initDebugMode();
	void initBackground();
	void initUI();
	void initLevel();
	void initPlayer();
	void initAsteroids();
	void spawnNewAsteroid();
	void checkCurrentWave();
	void checkCollisions();
	void createNewAsteroidColBox();
	void beginDraw();
	void endDraw();
	void loadTexture();

	UI* ui;
	Player* player1;
	//Player player2;
	std::vector<Asteroid*> asteroids;
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::RectangleShape playerColBox;
	std::vector<sf::RectangleShape> asteroidColBoxes;

	int currentWave;
	bool isDebugMode;
};