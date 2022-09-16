#pragma once
#include <SFML/System.hpp>

class FPS
{
	float deltaT;
	sf::Clock clock;

public:
	FPS();
	float getDeltaT();
	void update();
};
