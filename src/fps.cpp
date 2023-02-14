#include "fps.hpp"

FPS::FPS()
{
	mTimer.restart();
	deltaT = 0;
}

void FPS::update()
{
	deltaT = mTimer.getElapsedTime().asSeconds();
	mTimer.restart();
}

float FPS::getDeltaT()
{
	return deltaT;
}