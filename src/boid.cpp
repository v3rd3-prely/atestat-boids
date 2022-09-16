#include "boid.hpp"
#include "rest.hpp"
#include <cmath>

Boid::Boid()
{
	shape.setFillColor(sf::Color(255, 255, 255, 80));
	shape.setOutlineColor(sf::Color(255, 255, 255));
	shape.setOutlineThickness(1);
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(7, 0));
	shape.setPoint(1, sf::Vector2f(-7, 5));
	shape.setPoint(2, sf::Vector2f(-7, -5));
	speed = sf::Vector2f(0, 0);
	for(int i = 0; i < R_MAX; i++)
	{
		rays[i].set(pos, sf::Vector2f(0, 0));
	}
}

void Boid::contain(int width, int height)
{
	pos.x = (pos.x+15 < 0) ? width+15 : pos.x;
	pos.x = (pos.x-15 > width) ? -15 : pos.x;
	pos.y = (pos.y+15 < 0) ? height+15 : pos.y;
	pos.y = (pos.y-15 > height) ? -15 : pos.y;
}

void Boid::update(float deltaT, float p)
{
	float f = dist(force);
	force /= f;
	force *= (float)fmin(f, 3000.f);
	speed += (force*deltaT);
	float d = dist(speed);
	speed /= d;
	speed *= (float)fmax(fmin(d, 250.f), 100.f);
	speed *= 1.001f;
	force = sf::Vector2f(0, 0);
	pos += speed*deltaT;
	shape.setPosition(pos);
	float angle = atan2(speed.y, speed.x);
	shape.setRotation(angle/PI*180);
	for(int i = 0; i < R_MAX; i++)
	{
		float a = angle-PI*FOV/360.+(PI*FOV/180./float(R_MAX-1)*float(i));
		rays[i].set(pos, sf::Vector2f(p*cos(a), p*sin(a)));
	}
}

void Boid::steer(sf::Vector2f dir)
{
	force += dir;
}

void Boid::avoid(Wall *walls, unsigned int s)
{
	sf::Vector2f res;
	for(int i = 0; i < R_MAX; i++)
	{
		res = rays[i].collide(walls, s);
		if(res == sf::Vector2f(INT32_MIN, INT32_MIN))
			continue;
		res = pos-res;
		steer(res/(float)pow(dist(res), 3)*1000000.f);
	}
}

void Boid::think(Boid *boids, float s, float c, float a, float p)
{
	Boid mid;
	sf::Vector2f d;
	int index = 0;
	float aux = 200;
	mid.pos = sf::Vector2f(0, 0);
	mid.speed = sf::Vector2f(0, 0);
	steer(sf::Vector2f(random(-aux, aux), random(-aux, aux)));
	for(int i = 0; i < N_MAX; i++)
	{
		Boid &other = boids[i];
		if(this == &other)
			continue;
		if(dist(pos, other.pos) < p )
		{
			d = other.pos-pos;
			steer(-d/dist(pos, other.pos)*p/dist(pos, other.pos)*s);
			mid.pos += other.pos;
			mid.speed += other.speed;
			index++;
		}
	}
	if(index)
	{
		d = mid.pos/(float)index-pos;
		steer(d*c);
		d = mid.speed/(float)index-speed;
		steer(d*a);
	}
}

void Boid::show(sf::RenderWindow &window, bool ray)
{
	window.draw(shape);
	if(ray)
		for(int i = 0; i < R_MAX; i++)
		{
			window.draw(rays[i].shape);
		}
}


