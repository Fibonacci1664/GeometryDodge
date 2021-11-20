#include "Player.h"
#include <iostream>

Player::Player(int playerNum, sf::RenderWindow* hwnd, Input* in) : playerNum(playerNum), window(hwnd), input(in)
{
	position = sf::Vector2f(0.0f, 0.0f);
	velocity = sf::Vector2f(0.0f, 0.0f);
	speed = 7.0f;

	initPlayer();
	initGhost();
}

Player::~Player()
{
	
}

void Player::handleInput(float dt)
{
	// Handle player input
	position = input->getLeftStick();
}

void Player::update(float dt)
{
	if (playerDataMsgs.size() < 1)
	{
		return;
	}		

	PlayerDataMsg latestMessage = playerDataMsgs.back();
	//setPosition(latestMessage.x, latestMessage.y);

	sf::Vector2f position = sf::Vector2f(latestMessage.x, latestMessage.y);

	// update player
	//playerSprite.move(input->getLeftStick() * dt * speed);
	playerSprite.move(position * dt * speed);
	//playerSprite.setPosition(position);
	collisionBox = sf::FloatRect(playerSprite.getPosition().x - size.x * 0.4f, playerSprite.getPosition().y - size.y * 0.4f, size.x * 0.8f, size.y * 0.8f);
	checkScreenBounds();
}

void Player::render(sf::RenderWindow* window)
{
	switch (renderMode)
	{
		case RenderMode::PREDICTED_ONLY:
		{
			window->draw(playerGhostSprite);
			break;
		}
		case RenderMode::REAL_AND_PREDICTED:
		{
			window->draw(playerSprite);
			window->draw(playerGhostSprite);
			break;
		}
		case RenderMode::REAL_ONLY:
		{
			window->draw(*this);
			break;
		}
	}

	//window->draw(playerSprite);
}

void Player::addMessage(const PlayerDataMsg& msg)
{
	playerDataMsgs.push_back(msg);
}

sf::Vector2f Player::runPrediction(float gameTime)
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	const int msize = playerDataMsgs.size();

	if (msize < 3)
	{
		return sf::Vector2f(predictedX, predictedX);
	}

	const PlayerDataMsg& msg0 = playerDataMsgs[(size_t)msize - 1];		// Latest msg
	const PlayerDataMsg& msg1 = playerDataMsgs[(size_t)msize - 2];
	const PlayerDataMsg& msg2 = playerDataMsgs[(size_t)msize - 3];		// Oldest msg

	// FIXME: Implement prediction here!
	// You have:
	// - the history of position messages received, in "m_Messages"
	//   (msg0 is the most recent, msg1 the 2nd most recent, msg2 the 3rd most recent)
	// - the current time, in "gameTime"
	//
	// You need to update:
	// - the predicted position at the current time, in "predictedX" and "predictedY"

	// NO MODEL TASK
	/*predictedX = msg0.x;
	predictedY = msg0.y;*/
	
	sf::Vector2f predictedVec = linear(gameTime, msg0, msg1, msg2);
	////sf::Vector2f predictedVec = quadratic(gameTime, msg0, msg1, msg2);
	predictedX = predictedVec.x;
	predictedY = predictedVec.y;

	return sf::Vector2f(predictedX, predictedY);
}

sf::Vector2f Player::linear(float gameTime, const PlayerDataMsg& msg0, const PlayerDataMsg& msg1, const PlayerDataMsg& msg2)
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	// LINEAR MODEL TASK (VEL ONLY) using s = vt
	sf::Vector2f prevPrevPos = sf::Vector2f(msg1.x, msg1.y);
	sf::Vector2f prevPos = sf::Vector2f(msg0.x, msg0.y);
	sf::Vector2f distanceVec = prevPos - prevPrevPos;
	float dist = std::hypot(distanceVec.x, distanceVec.y);
	float deltaTime = msg0.timeSent - msg1.timeSent;
	float speed = dist / deltaTime;
	float displacement = speed * (gameTime - msg0.timeSent);
	sf::Vector2f nextPos = sf::Vector2f(msg0.x + displacement, msg0.y + displacement);
	predictedX = nextPos.x;
	predictedY = nextPos.y;

	return sf::Vector2f(predictedX, predictedY);
}

sf::Vector2f Player::quadratic(float gameTime, const PlayerDataMsg& msg0, const PlayerDataMsg& msg1, const PlayerDataMsg& msg2)
{
	float predictedX = -1.0f;
	float predictedY = -1.0f;

	// QUADRACTIC MODEL TASK (USING ACC AND VEL) using s = ut + 0.5 * at^2
	float prevDeltaTime = msg0.timeSent - msg1.timeSent;
	float prevPrevDeltaTime = msg1.timeSent - msg2.timeSent;
	sf::Vector2f changeInXY_Prev = sf::Vector2f((msg0.x - msg1.x), (msg0.y - msg1.y));
	sf::Vector2f changeInXY_PrevPrev = sf::Vector2f((msg1.x - msg2.x), (msg1.y - msg2.y));
	float prevSpeed = abs(changeInXY_Prev.x - changeInXY_Prev.y) / prevDeltaTime;
	float prevPrevSpeed = abs(changeInXY_PrevPrev.x - changeInXY_PrevPrev.y) / prevPrevDeltaTime;
	float deltaSpeed = prevSpeed - prevPrevSpeed;
	float accel = deltaSpeed / prevDeltaTime;
	float displacement = prevSpeed * (gameTime - msg0.timeSent) + 0.5f * accel * pow(gameTime, 2);
	sf::Vector2f nextPos = sf::Vector2f(msg0.x + displacement, msg0.y + displacement);
	predictedX = nextPos.x;
	predictedY = nextPos.y;

	return sf::Vector2f(predictedX, predictedY);
}

void Player::initPlayer()
{
	loadTexture();
	playerTexture.setSmooth(true);
	playerSprite.setTexture(playerTexture);
	size = playerTexture.getSize();
	playerSprite.setOrigin(size.x * 0.5f, size.y * 0.5f);
	playerSprite.setPosition(sf::Vector2f(200.0f, 200.0f));
	playerSprite.setScale(0.75f, 0.75f);
	collisionBox = sf::FloatRect(playerSprite.getPosition().x - size.x * 0.4f, playerSprite.getPosition().y - size.y * 0.4f, size.x * 0.8f, size.y * 0.8f);
}

void Player::initGhost()
{
	playerGhostSprite.setTexture(playerTexture);
	playerGhostSprite.setColor(sf::Color(255, 255, 255, 128));
	size = playerTexture.getSize();
	playerGhostSprite.setOrigin(size.x * 0.5f, size.y * 0.5f);
	playerGhostSprite.setPosition(playerSprite.getPosition());
	playerGhostSprite.setScale(0.75f, 0.75f);
}

void Player::loadTexture()
{
	if (!playerTexture.loadFromFile("res/gfx/ships/altShip_" + std::to_string(playerNum) + ".png"))
	{
		std::cout << "Error loading ship texture " << playerNum << '\n';
	}
}

void Player::checkScreenBounds()
{
	// Check left edge of screen
	if (playerSprite.getPosition().x - (size.x * 0.5f) < 0)
	{
		playerSprite.setPosition(sf::Vector2f(size.x * 0.5f, playerSprite.getPosition().y));
	}

	// Check right edge of screen
	if (playerSprite.getPosition().x + (size.x * 0.5f) > window->getSize().x)
	{
		playerSprite.setPosition(sf::Vector2f(window->getSize().x - size.x * 0.5f, playerSprite.getPosition().y));
	}

	// Check top edge of screen
	if (playerSprite.getPosition().y - (size.y * 0.5f) < 0)
	{
		playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, size.y * 0.5f));
	}

	// Check btm edge of screen
	if (playerSprite.getPosition().y + (size.y * 0.5f) > window->getSize().y)
	{
		playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, window->getSize().y - size.y * 0.5f));
	}
}

void Player::setGhostPosition(sf::Vector2f pos, float dt)
{
	playerGhostSprite.move(pos * dt * speed);
}

sf::Vector2u* Player::getPlayerSize()
{
	return &size;
}

sf::FloatRect Player::getCollisionBox()
{
	return collisionBox;
}

void Player::setCollisionBox(float x, float y, float width, float height)
{
	collisionBox = sf::FloatRect(x, y, width, height);
}

sf::Vector2f Player::getPosition()
{
	return position;
}

void Player::reset()
{
	playerDataMsgs.clear();
}
