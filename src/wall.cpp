#include "wall.hpp"

Wall::Wall(sf::Vector2f po1, sf::Vector2f po2)
{
	p1 = po1;
	p2 = po2;
	vertical = p2.x == p1.x;
	a = (p2.y-p1.y)/(p2.x-p1.x);
	b = p1.y-a*p1.x;
	shape.setPointCount(4);
	shape.setPoint(0, p1);
	shape.setPoint(1, p2);
	shape.setPoint(2, p2);
	shape.setPoint(3, p1);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color(255, 0, 0, 255));
}

Wall::Wall()
{
	
}

void Wall::show(sf::RenderWindow &window)
{
	window.draw(shape);
}

