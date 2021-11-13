#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	~Player();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	float speed;
};

