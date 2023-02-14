#pragma once
#include <SFML/System.hpp>

class FPS
{
	float deltaT;
	sf::Clock mTimer;

public:
	FPS();
	float getDeltaT();
	void update();
};
