#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class UI
{
public:
	UI();
	~UI();

	void update(float dt);
	sf::Text* getWaveText();
	sf::Text* getCountdownText();
	int getWaveCount();

private:
	void initUI();
	void loadFont();

	sf::Font font;
	sf::Text waveText;
	sf::Text countdownText;

	int waveCount;
	int timer;
	float count;
};