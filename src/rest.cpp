#include "rest.hpp"
#include <cstdlib>
#include <cmath>

float dist(const sf::Vector2f& a, const sf::Vector2f& b)
{
	float x = a.x-b.x, y = a.y-b.y;
	return sqrt(x*x + y*y);
}

int random(int const &mi, int const &ma)
{
	return rand()%(ma-mi)+mi;
}