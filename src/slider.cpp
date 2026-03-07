#include "slider.hpp"
#include <string>
#include <iostream>
#include <cmath>

using sf::Mouse;
using sf::Color;

Slider::Slider()
{
	int radius = 15;
	mIndicator.setOrigin(radius, radius);
	mIndicator.setRadius(radius);
	mIndicator.setFillColor(Color(100, 200, 100, 255));
	mIndicator.setOutlineColor(Color(0, 0, 0, 100));
	mIndicator.setOutlineThickness(6);

	mTrack.setPoints(sf::Vector2f(0, 0), sf::Vector2f(mWidth, 0));
	mTrack.roundEdges(3, 5);
	mTrack.mShape.setFillColor(Color(255, 255, 255, 150));
	mTrack.mShape.setOutlineColor(Color(0, 0, 0, 100));
	mTrack.mShape.setOutlineThickness(4);

	mText.setString(std::to_string(int(mValue)));
	mText.setOutlineColor(Color(0, 0, 0));
	mText.setOutlineThickness(3);

	mTitle.setOutlineColor(Color(0, 0, 0));
	mTitle.setOutlineThickness(3);
}

Slider::Slider(int x, int y, const char* name)
{
	Slider();
	setPosition(x, y);
	setName(name);
}

void Slider::setValues(int minimum, int maximum)
{
	mMinValue = minimum;
	mMaxValue = maximum;
}

void limit(int& value, int mi, int ma)
{
	value = std::max(std::min(value, ma), mi);
}

// linear interpolation
int lerp(int value, int minIn, int maxIn, int minOut, int maxOut)
{
	return ((value-minIn)*(maxOut-minOut)/(maxIn-minIn) + minOut);
}

void Slider::check()
{
	bool isMousePressed = Mouse::isButtonPressed(Mouse::Left);
	bool isMouseInside = mIndicator.getGlobalBounds().contains(Mouse::getPosition(*mWindow).x, Mouse::getPosition(*mWindow).y);

	isMouseInside = isMouseInside || isHolded;

	isHolded = isMousePressed && isMouseInside;

	if(!isHolded)
		return;
	
	int mouseX = Mouse::getPosition(*mWindow).x;
	auto position = mTrack.mShape.getPosition();
	limit(mouseX, position.x, position.x+mWidth);
	mValue = lerp(mouseX, position.x, position.x+mWidth, mMinValue, mMaxValue);

	mIndicator.setPosition(mouseX, position.y);
	mText.setString(std::to_string(int(mValue)));
}

void Slider::setName(const char* name)
{
	mTitle.setString(std::string(name));
}

float Slider::getValue()
{
	return mValue;
}

void Slider::show()
{	
	mWindow->draw(mTrack.mShape);
	mWindow->draw(mIndicator);
	mWindow->draw(mText);
	mWindow->draw(mTitle);	
}

void Slider::setFont(sf::Font& font)
{
	mText.setFont(font);
	mTitle.setFont(font);
}

void Slider::setPosition(float x, float y)
{
	mIndicator.setPosition(x, y);
	mTrack.mShape.setPosition(x, y);
	mText.setPosition(x+mWidth-60, y-60.f);
	mTitle.setPosition(x, y-60.f);
}
