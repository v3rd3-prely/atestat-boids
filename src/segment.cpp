#include "segment.hpp"
#include "rest.hpp"
#include <cmath>

using sf::Vector2f;

void Segment::setPoints(Vector2f point1, Vector2f point2)
{
	mPoint1 = point1;
	mPoint2 = point2;
	// mShape.setPosition(point1);
	isVertical = mPoint2.x == mPoint1.x;
	if(isVertical)
	{
		a = 0;
		b = mPoint1.x;
	}
	else
	{
		a = (mPoint2.y-mPoint1.y)/(mPoint2.x-mPoint1.x);
		b = mPoint1.y-a*mPoint1.x;
	}
}

void Segment::roundEdges(float thickness, int accuracy)
{
	float angle = atan2((mPoint1-mPoint2).x, (mPoint1-mPoint2).y);
	mShape.setPointCount(2*accuracy);
	for(int i = 0; i < accuracy; i++)
	{
		float currentAngle = angle-PI/2.f +(PI*i/(float)(accuracy-1));
		auto aux = sf::Vector2f(sin(currentAngle), cos(currentAngle))*thickness;
		mShape.setPoint(i, mPoint1+aux);
		mShape.setPoint(i+accuracy, mPoint2-aux);
	}
}


bool Segment::doesIntersect(Segment &other, Vector2f &intersection)
{
	if(other.a == a && isVertical == other.isVertical)
			return false;
		
		if(isVertical)
		{
			intersection.x = b;
			intersection.y = other.a*intersection.x+other.b;
		}
		else if(other.isVertical)
		{
			intersection.x = other.b;
			intersection.y = a*intersection.x+b;
		}
		else
		{
			intersection.x = (other.b-b)/(a-other.a);
			intersection.y = a*intersection.x+b;
		}

	bool isInsideThis = (abs(intersection.x-mPoint1.x)+abs(intersection.x-mPoint2.x)) <= abs(mPoint1.x-mPoint2.x)+0.01;
	bool isInsideOther = (abs(intersection.x-other.mPoint1.x)+abs(intersection.x-other.mPoint2.x)) <= abs(other.mPoint1.x-other.mPoint2.x)+0.01;
	return isInsideThis && isInsideOther;
}
