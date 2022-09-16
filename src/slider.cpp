#include "slider.hpp"
#include <string>

Slider::Slider(int x, int y, const char* n)
{
	pos.x = x;
	pos.y = y;
	minVal = 0;
	maxVal = 100;
	value = 0;
	hold = false;
	width = 300;
	
	name.setString(std::string(n));

	int radius = 15;
	slider.setPosition(pos);
	slider.setOrigin(radius, radius);
	slider.setRadius(radius);
	slider.setFillColor(sf::Color(200, 255, 100, 100));
	axis.setPosition(pos);
	axis.setOrigin(0, 1);
	axis.setSize(sf::Vector2f(width, 2));

	font.loadFromFile("fonts/arial.ttf");
	text.setFont(font);
	text.setString(std::to_string(int(value)));
	text.setPosition(pos);
	name.setFont(font);
	name.setPosition(pos.x, pos.y-50);
	name.setOutlineColor(sf::Color(0, 0, 0));
	name.setOutlineThickness(3);

}

void Slider::setValues(int mi, int ma)
{
	minVal = mi;
	maxVal = ma;
}

void Slider::check(sf::RenderWindow &window)
{
	if(!hold)
	{

		hold = slider.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		hold *= sf::Mouse::isButtonPressed(sf::Mouse::Left);
	}
	else
		hold = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	if(hold)
	{
		int x = sf::Mouse::getPosition(window).x;
		slider.setPosition(std::max(std::min(x, int(pos.x+width)), int(pos.x)), pos.y);
		value = (minVal + ((slider.getPosition().x - pos.x) / width * (maxVal - minVal)));
		text.setString(std::to_string(int(value)));
	}
}

void Slider::setName(const char* n)
{
	name.setString(std::string(n));
}

void Slider::show(sf::RenderWindow &window)
{
	window.draw(slider);
	window.draw(axis);
	window.draw(text);
	window.draw(name);
}

