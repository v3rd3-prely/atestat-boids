#include "ray.hpp"
#include "segment.hpp"
#include <cmath>
#include "rest.hpp"

using sf::Vector2f;

Ray::Ray()
{
	mShape.setOutlineThickness(3);
	mShape.setOutlineColor(sf::Color(255, 150, 0, 15));
}

void Ray::setPoints(Vector2f point1, Vector2f point2)
{
	Segment::setPoints(point1, point2);
	mShape.setPointCount(4);
	mShape.setPoint(0, mPoint1);
	mShape.setPoint(1, mPoint2);
	mShape.setPoint(2, mPoint2);
	mShape.setPoint(3, mPoint1);
}

void Ray::set(Vector2f point, Vector2f offset)
{
	setPoints(point, point+offset);
}

Vector2f Ray::collide(Wall *walls)
{
	Vector2f result(INT32_MIN, INT32_MIN), intersection(0, 0);
	for(int i = 0; i < A_MAX; i++)
	{
		if(!doesIntersect(walls[i], intersection))
			continue;
		result = (dist(mPoint1, result) > dist(mPoint1, intersection)) ? intersection : result;
	}
	return result;
}

