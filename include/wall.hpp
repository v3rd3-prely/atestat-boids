#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Wall
{
public:
	sf::Vector2f p1, p2;
	sf::ConvexShape shape;
	float a, b;
	bool vertical;

	Wall(sf::Vector2f po1, sf::Vector2f po2);
	Wall();
	void show(sf::RenderWindow &window);
};