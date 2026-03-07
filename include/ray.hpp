#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "wall.hpp"
#include "segment.hpp"


class Ray : public Segment
{
public:

	Ray();
	void set(sf::Vector2f point1, sf::Vector2f point2);
	sf::Vector2f collide(Wall* walls);
	void setPoints(sf::Vector2f point1, sf::Vector2f point2);
};