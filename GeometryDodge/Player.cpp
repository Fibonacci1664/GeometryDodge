#include "Player.h"
#include <iostream>

Player::Player(int playerNum) : playerNum(playerNum)
{
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 7.0f;
	input = nullptr;

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
	playerSprite.move(input->getLeftStick() * dt * speed);
}

void Player::initPlayer()
{
	loadTexture();
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	playerSprite.setOrigin(getTextureRect().width * 0.5f, getTextureRect().height * 0.5f);
	playerSprite.setPosition(sf::Vector2f(200.0f, 200.0f));
	//playerSprite.setScale(2.0f, 2.0f);
}

void Player::loadTexture()
{
	if (!playerTexture.loadFromFile("res/gfx/ships/altShip_" + std::to_string(playerNum) + ".png"))
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