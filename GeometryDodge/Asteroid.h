#pragma once
#include <SFML/Graphics.hpp>

class Asteroid
{
public:
	Asteroid(sf::RenderWindow* hwnd);
	~Asteroid();

	void update(float dt);
	sf::Sprite* getAsteroidSprite();

private:
	void initAsteroid();
	void loadTexture();
	void checkScreenBounds();
	void move();

	sf::RenderWindow* window;
	sf::Texture asteroidTexture;
	sf::Sprite asteroidSprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2u size;
	float randSpeed;		// Add this later if the MVP works
	int randXPos;
	int randYPos;
};