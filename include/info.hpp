#pragma once

#include <SFML/Graphics.hpp>
#include "showable.hpp"
class Info : public Showable
{
	sf::Text mText;
	bool isVisible = false, isPressed = false;
public:
	Info();
	void update();
	void show();
	void setFont(sf::Font& font);
	void setText(const char *text);
};