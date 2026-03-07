#include "wall.hpp"
#include <cmath>

Wall::Wall()
{
	mShape.setFillColor(sf::Color(200, 50, 50));
	mShape.setOutlineThickness(4);
	mShape.setOutlineColor(sf::Color(0, 0, 0, 100));
}

Wall::Wall(sf::Vector2f point1, sf::Vector2f point2)
{
	*this = Wall();
	setPoints(point1, point2);
}

void Wall::setPoints(sf::Vector2f point1, sf::Vector2f point2)
{
	Segment::setPoints(point1, point2);
	roundEdges(3, 5);
}

void Wall::show()
{
	mWindow->draw(mShape);
}
