#include "ray.hpp"
#include <cmath>
#include "rest.hpp"

Ray::Ray()
{
	p1 = sf::Vector2f(0, 0);
	p2 = sf::Vector2f(0, 0);
	vertical = false;
}

void Ray::set(sf::Vector2f po1, sf::Vector2f po2)
{
	p1 = po1;
	p2 = po2+po1;
	vertical = p2.x == p1.x;
	a = (p2.y-p1.y)/(p2.x-p1.x);
	b = p1.y-(a*p1.x);
	shape.setPointCount(4);
	shape.setPoint(0, p1);
	shape.setPoint(1, p2);
	shape.setPoint(2, p2);
	shape.setPoint(3, p1);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color(255, 255, 0, 30));
}

sf::Vector2f Ray::collide(Wall *walls, unsigned int s)
{
	sf::Vector2f res(INT32_MIN, INT32_MIN), p(0, 0);
	for(int i = 0; i < s; i++)
	{
		Wall &w = walls[i];
		if(w.a == a || (vertical && w.vertical))
			continue;
		if(vertical)
		{
			p.x = p1.x;
			p.y = w.a*p.x+w.b;
		}
		if(w.vertical)
		{
			p.x = w.p1.x;
			p.y = a*p.x+b;
		}
		if(!vertical && !w.vertical)
		{
			p.x = (w.b-b)/(a-w.a);
			p.y = a*p.x+b;
		}
		if(abs(p.x-p1.x)+abs(p.x-p2.x) <= abs(p1.x-p2.x) && abs(p.x-w.p1.x)+abs(p.x-w.p2.x) <= abs(w.p1.x-w.p2.x) &&
		abs(p.y-p1.y)+abs(p.y-p2.y) <= abs(p1.y-p2.y) && abs(p.y-w.p1.y)+abs(p.y-w.p2.y) <= abs(w.p1.y-w.p2.y))
		{
			res = (dist(p1, res) > dist(p1, p)) ? p : res;
		}
	}
	return res;
}

