#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "wall.hpp"


class Ray
{
public:
	sf::Vector2f p1, p2;
	sf::ConvexShape shape;
	float a, b;
	bool vertical;

	Ray();
	void set(sf::Vector2f po1, sf::Vector2f po2);
	sf::Vector2f collide(Wall *walls, unsigned int s);
};