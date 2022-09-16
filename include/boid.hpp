#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include "ray.hpp"
#include "rest.hpp"

class Boid
{
public:
	sf::Vector2f pos, speed, force;
	sf::ConvexShape shape;
	Ray rays[R_MAX];

	Boid();
	void update(float deltaT, float p);
	void show(sf::RenderWindow &window, bool ray);
	void contain(int width, int height);
	void steer(sf::Vector2f dir);
	void avoid(Wall *walls, unsigned int s);
	void think(Boid *boids, float s, float c, float a, float p);
};