#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "ray.hpp"
#include "rest.hpp"
#include "showable.hpp"
class Boid : public Showable
{
	sf::Vector2f mPosition, mVelocity, mAcceleration;
	sf::ConvexShape mShape;
	Ray mRays[R_MAX];
public:

	Boid();
	void update(float deltaT = 0);
	void updateRays(float perception);
	void show();
	void showRays();
	void wrap();
	void setPosition(sf::Vector2f position);
	void setVelocity(sf::Vector2f velocity);

	void steer(sf::Vector2f direction);
	void avoid(Wall *walls);
	void flock(Boid *boids, float *params);
};