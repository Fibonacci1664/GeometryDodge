#pragma once
#include <SFML/Graphics.hpp>

class Player : sf::Sprite
{
public:
	Player() {}
	Player(int playerNum);
	~Player();

	void handleInput(float dt);
	void update(float dt);
	sf::Sprite* getPlayerSprite();

private:
	void initPlayer();
	void loadTexture();
	
	void move();

	sf::Texture spriteTexture;
	sf::Sprite playerSprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	int playerNum;
	float speed;
};

