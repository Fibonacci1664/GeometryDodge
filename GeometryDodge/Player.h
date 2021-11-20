#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Input.h"
#include "PlayerDataMsg.h"

enum class RenderMode{ REAL_ONLY, PREDICTED_ONLY, REAL_AND_PREDICTED };

class Player : sf::Sprite
{
public:
	Player() {}
	Player(int playerNum, sf::RenderWindow* hwnd, Input* in);
	~Player();

	void handleInput(float dt);
	void update(float dt);
	void render(sf::RenderWindow* window);

	void addMessage(const PlayerDataMsg& msg);
	sf::Vector2f runPrediction(float gameTime);

	void setRenderMode(const RenderMode rdrMode) { renderMode = rdrMode; }
	void setGhostPosition(sf::Vector2f pos, float dt);
	//sf::Sprite* getPlayerSprite();
	sf::Vector2u* getPlayerSize();
	sf::FloatRect getCollisionBox();
	void setCollisionBox(float x, float y, float width, float height);
	sf::Vector2f getPosition();
	void reset();

private:
	void initPlayer();
	void initGhost();
	void loadTexture();
	void checkScreenBounds();
	sf::Vector2f linear(float gameTime, const PlayerDataMsg& msg0, const PlayerDataMsg& msg1, const PlayerDataMsg& msg2);
	sf::Vector2f quadratic(float gameTime, const PlayerDataMsg& msg0, const PlayerDataMsg& msg1, const PlayerDataMsg& msg2);


	Input* input;
	sf::RenderWindow* window;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	sf::Sprite playerGhostSprite;
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2u size;
	sf::FloatRect collisionBox;

	RenderMode	renderMode = RenderMode::REAL_AND_PREDICTED;
	std::vector<PlayerDataMsg> playerDataMsgs;

	int playerNum;
	float speed;
	
};

