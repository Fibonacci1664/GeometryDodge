#include "Player.h"
#include <iostream>

Player::Player(int playerNum) : playerNum(playerNum)
{
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 0.0f;

	initPlayer();
}

Player::~Player()
{

}

void Player::handleInput(float dt)
{
	// Handle player input
}

void Player::update(float dt)
{
	// update player
}

void Player::initPlayer()
{
	loadTexture();
	spriteTexture.setSmooth(true);
	playerSprite.setTexture(spriteTexture);
	playerSprite.setOrigin(getTextureRect().width * 0.5f, getTextureRect().height * 0.5f);
	playerSprite.setPosition(sf::Vector2f(50.0f, 50.0f));
	playerSprite.setScale(2.0f, 2.0f);
}

void Player::loadTexture()
{
	if (!spriteTexture.loadFromFile("res/gfx/ships/ship_" + std::to_string(playerNum) + ".png"))
	{
		std::cout << "Error loading ship texture " << playerNum << '\n';
	}
}

void Player::move()
{

}

sf::Sprite* Player::getPlayerSprite()
{
	return &playerSprite;
}