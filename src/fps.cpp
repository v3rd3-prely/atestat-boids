#include "fps.hpp"

FPS::FPS()
{
	clock.restart();
	deltaT = 0;
}

void FPS::update()
{
	deltaT = clock.getElapsedTime().asSeconds();
	clock.restart();
}

float FPS::getDeltaT()
{
	return deltaT;
}