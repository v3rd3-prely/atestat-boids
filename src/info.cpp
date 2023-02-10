#include "info.hpp"

Info::Info()
{
	font.loadFromFile("../fonts/arial.ttf");
	text.setFont(font);
	text.setOutlineColor(sf::Color(0, 0, 0));
	text.setOutlineThickness(4);
	text.setString(" Press Space to pause\n Press S to show rays\n Press N to reset boids\n Press Esc to exit");
	text.setPosition(0, 0);
}

void Info::show(sf::RenderWindow &window)
{
	if(toggle)
		window.draw(text);
}

void Info::update()
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
		{
			pressed = true;
		}
		if(cooldown.getElapsedTime().asMilliseconds() > 50)
		{
			toggle = pressed;
			pressed = false;
			cooldown.restart();
		}
}