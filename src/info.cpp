#include "info.hpp"

Info::Info()
{
	mText.setOutlineColor(sf::Color(0, 0, 0));
	mText.setOutlineThickness(3);
	mText.setPosition(20, 10);
	mText.setStyle(sf::Text::Bold);
	mText.setString("");
}

void Info::setText(const char *text)
{
	mText.setString(text);
}

void Info::show()
{
	if(!isVisible)
		return;
	mWindow->draw(mText);
}

void Info::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		isPressed = true;
	}
	isVisible = isPressed;
	isPressed = false;
}

void Info::setFont(sf::Font& font)
{
	mText.setFont(font);
}
