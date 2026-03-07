#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "rest.hpp"

class Showable{
protected:
	sf::RenderWindow *mWindow = nullptr;
public:
	void setWindow(sf::RenderWindow &window);
};