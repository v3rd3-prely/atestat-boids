#pragma once
#include <SFML/Graphics.hpp>

class Slider
{
public:
	sf::CircleShape slider;
	sf::RectangleShape axis;
	sf::Vector2f pos;
	int minVal, maxVal, width;
	float value;
	sf::Font font;
	sf::Text text, name;
	bool hold;

	Slider(int x, int y, const char* n);
	void setValues(int mi, int ma);
	void setName(const char* n);
	void check(sf::RenderWindow &window);
	void show(sf::RenderWindow &window);
};