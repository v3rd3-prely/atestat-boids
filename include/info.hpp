#pragma once

#include <SFML/Graphics.hpp>

class Info
{
	sf::Clock cooldown;
	sf::Font font;
	sf::Text text;
	bool toggle, pressed;
public:
	Info();
	void update();
	void show(sf::RenderWindow &window);
};