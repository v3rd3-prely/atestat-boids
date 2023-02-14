#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

class Segment
{
public:
	sf::Vector2f mPoint1 = sf::Vector2f(0, 0), mPoint2 = sf::Vector2f(0, 0);
	sf::ConvexShape mShape;
	float a = 0, b = 0;
	bool isVertical = false;

// public:
	// Segment();
	void setPoints(sf::Vector2f point1, sf::Vector2f point2);
	bool doesIntersect(Segment &other, sf::Vector2f &intersection);
	void roundEdges(float thickness, int accuracy);
};