#pragma once
#include <SFML/Graphics.hpp>
#include "showable.hpp"
#include "segment.hpp"

class Slider : public Showable
{
	sf::CircleShape mIndicator;
	Segment mTrack;
	int mMinValue = 0, mMaxValue = 100, mWidth = 300;
	bool isHolded = false;
	sf::Text mText, mTitle;
	float mValue = 0;
public:

	Slider();
	Slider(int x, int y, const char* name);
	void setPosition(float x, float y);
	void setValues(int minimum, int maximum);
	void setFont(sf::Font& font);
	void setName(const char* name);
	float getValue();
	void check();
	void show();
};