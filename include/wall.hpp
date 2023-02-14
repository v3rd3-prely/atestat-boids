#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "showable.hpp"
#include "segment.hpp"

class Wall : public Showable, public Segment
{
public:
	Wall();
	Wall(sf::Vector2f point1, sf::Vector2f point2);
	void setPoints(sf::Vector2f point1, sf::Vector2f point2);
	void show();
};