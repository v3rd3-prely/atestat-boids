#include "boid.hpp"
#include "rest.hpp"
#include <cmath>

using sf::Vector2f;

Boid::Boid()
{
	mShape.setFillColor(sf::Color(150, 200, 255, 250));
	mShape.setOutlineColor(sf::Color(0, 0, 0, 60));
	mShape.setOutlineThickness(2);

	mShape.setPointCount(4);
	float scalar = 5;
	mShape.setPoint(0,  Vector2f(1,  0)*scalar);
	mShape.setPoint(1,  Vector2f(-0.5,  0.8)*scalar);
	mShape.setPoint(2,  Vector2f(-1,  0)*scalar);
	mShape.setPoint(3,  Vector2f(-0.5,  -0.8)*scalar);

	mVelocity = Vector2f(0, 0);
	for(int i = 0; i < R_MAX; i++)
	{
		mRays[i].set(mPosition, Vector2f(0, 0));
	}
}

void Boid::wrap()
{
	auto position = mWindow->getSize();
	mPosition.x = (mPosition.x+15 < 0) ? position.x+15 : mPosition.x;
	mPosition.x = (mPosition.x-15 > position.x) ? -15 : mPosition.x;
	mPosition.y = (mPosition.y+15 < 0) ? position.y+15 : mPosition.y;
	mPosition.y = (mPosition.y-15 > position.y) ? -15 : mPosition.y;
	mShape.setPosition(mPosition);
}

void Boid::setPosition(sf::Vector2f position)
{
	mPosition = position;
}

void Boid::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Boid::update(float deltaT)
{
	int range = 300;
	steer(Vector2f(random(-range, range), random(-range, range)));

	// format force
	float f = dist(mAcceleration);
	if(f < 0.1)
		f = 0.1;
	mAcceleration /= f;
	mAcceleration *= (float)fmin(f, 1000.f);

	// format speed
	float d = dist(mVelocity);
	mVelocity /= d;
	mVelocity *= (float)fmin(d, 100.f);
	mVelocity *= 1.1f;

	mPosition += mVelocity*deltaT+(mAcceleration*deltaT*deltaT/2.f);
	mVelocity += (mAcceleration*deltaT);

	// reset force
	mAcceleration = Vector2f(0, 0);

	mShape.setPosition(mPosition);
	float angle = atan2(mVelocity.y, mVelocity.x);
	mShape.setRotation(angle/PI*180);
}

void Boid::updateRays(float perception)
{
	float angle = mShape.getRotation()/180.*PI;
	for(int i = 0; i < R_MAX; i++)
	{
		float a = angle-PI*FOV/360.+(PI*FOV/180./float(R_MAX-1)*float(i));
		mRays[i].set(mPosition, Vector2f(perception*cos(a), perception*sin(a)));
	}
}

void Boid::steer(Vector2f direction)
{
	mAcceleration += direction;
}

void Boid::avoid(Wall *walls)
{
	Vector2f result;
	float distance;
	for(int i = 0; i < R_MAX; i++)
	{
		result = mRays[i].collide(walls);
		if(dist(result) > 10000)
			continue;
		result = mPosition-result;
		distance = dist(result);
		result /= distance;
		steer(result*10.f*(float)pow(1.3, 40-distance));
	}
}

void Boid::flock(Boid *boids, float *params)
{
	// Boid mid;
	Vector2f averagePosition(0, 0);
	Vector2f averageDirection(0, 0);
	Vector2f distance;
	float averageVelocityValue = 0;
	float distanceValue;
	int index = 0;

	for(int i = 0; i < N_MAX; i++)
	{
		Boid &other = boids[i];
		if(this == &other)
			continue;
		distanceValue = dist(other.mPosition, mPosition);
		if(distanceValue > params[3])
			continue;

		distance = other.mPosition-mPosition;
		// steer(-distance/distanceValue*params[0]);
		steer(-distance/distanceValue*(float)pow(1.1, (2*params[0])-distanceValue));
		averagePosition += other.mPosition;
		averageDirection += other.mVelocity/dist(other.mVelocity);
		averageVelocityValue += dist(other.mVelocity);
		index++;
	}
	if(!index)
		return;
	auto targetPosition = averagePosition/(float)index-mPosition;
	steer(targetPosition*params[1]);

	averageDirection = averageDirection/dist(averageDirection);
	averageVelocityValue /= (float)index;
	auto targetDirection = averageDirection*averageVelocityValue-mVelocity;
	steer(targetDirection*params[2]);
}

void Boid::show()
{
	mWindow->draw(mShape);
}

void Boid::showRays()
{
	for(Ray &ray : mRays)
		mWindow->draw(ray.mShape);
}
