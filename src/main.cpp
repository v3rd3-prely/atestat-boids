#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <cmath>
#include <iostream>

#include "fps.hpp"
#include "boid.hpp"
#include "wall.hpp"
#include "slider.hpp"
#include "rest.hpp"
#include "info.hpp"
#include "showable.hpp"

using namespace sf;

int main()
{
	bool isPaused = true, shouldShowRays = true, shouldShowSliders = true;
	float parameters[4];
	float frameSpeed;
	std::string text, frameString;
	
	Info info;
	RenderWindow window;
	Boid boids[N_MAX];
	Wall walls[A_MAX];
	Event event;
	FPS timer;
	Font arial;
	Slider sliders[4];

	// SETUP

	srand(time(NULL));
	arial.loadFromFile("../fonts/arial.ttf");
	window.create(VideoMode::getDesktopMode(), "Boids", Style::Fullscreen);
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);

	info.setWindow(window);
	info.setFont(arial);
	text += "Press Space to pause / play\n";
	text += "Press S to show / hide rays\n";
	text += "Press E to show / hide sliders and cursor\n";
	text += "Press N to reset boids and walls\n";
	text += "Press Esc to exit\n";
	info.setText(text.c_str());

	int yValue = window.getSize().y- 50;
	for(int i = 0; i < 4; i++)
	{
		sliders[i].setWindow(window);
		sliders[i].setFont(arial);
		sliders[i].setPosition(30, yValue-100*i);
	}
	sliders[0].setName("Separation");
	sliders[1].setName(  "Cohesion");
	sliders[2].setName("Alignement");
	sliders[3].setName("Perception");

	for(Boid &boid : boids)
		boid.setWindow(window);
	for(Wall &wall : walls)
		wall.setWindow(window);

	// DRAW
	auto draw = [&]()
	{
		if(shouldShowRays)
			for(Boid &boid : boids)
				boid.showRays();

		for(Wall &wall : walls)
			wall.show();
		
		for(Boid &boid : boids)
			boid.show();

		info.show();

		if(shouldShowSliders)
			for(Slider &slider : sliders)
				slider.show();
	};

	// LOOP

	auto loop = [&]()
	{
		timer.update();
		frameSpeed = 1/timer.getDeltaT();
		info.setText(("FPS: "+std::to_string(frameSpeed).substr(0, 5)+"\n"+text).c_str());
		info.update();

		for(Boid &boid : boids)
		{
			boid.updateRays(parameters[3]);

			if(isPaused)
				continue;

			boid.avoid(walls);
			boid.flock(boids, parameters);
			boid.update(timer.getDeltaT());
			boid.wrap();
		}

		if(!shouldShowSliders)
			return;

		for(Slider &slider : sliders)
			slider.check();

		parameters[0] = pow(sliders[0].getValue(), 0.8)*SEPARATION;
		parameters[1] = sliders[1].getValue()*COHESION;
		parameters[2] = sliders[2].getValue()*ALIGNMENT;
		parameters[3] = pow(sliders[3].getValue(), 3)*PERCEPTION;
	};

	// RESET BOIDS AND WALLS

	auto refresh = [&](){
		for(Boid &boid : boids)
		{
			float range = 100;
			float margin = 15;
			float randomX = random(margin, window.getSize().x-margin);
			float randomY = random(margin, window.getSize().y-margin);

			boid.setPosition(Vector2f(randomX, randomY));
			boid.setVelocity(Vector2f(random(-range, range), random(-range, range)));
			boid.update();
		}
		for(Wall &wall : walls)
		{
			float rx1 = random(0, window.getSize().x);
			float ry1 = random(0, window.getSize().y);
			float rx2 = random(-500, 500);
			float ry2 = random(-500, 500);
			wall.setPoints(Vector2f(rx1, ry1), Vector2f(rx1+rx2, ry1+ry2));
		}
		if(!BORDER)
			return;
		
		walls[0].setPoints(Vector2f(0, 0), Vector2f(window.getSize().x, 0));
		walls[1].setPoints(Vector2f(window.getSize().x, 0), Vector2f(window.getSize().x, window.getSize().y));
		walls[2].setPoints(Vector2f(window.getSize().x, window.getSize().y), Vector2f(0, window.getSize().y));
		walls[3].setPoints(Vector2f(0, window.getSize().y), Vector2f(0, 0));
	};

	// QUERRY EVENTS

	auto events = [&](){
		while (window.pollEvent(event))
		{
			switch(event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::Space:
					isPaused = !isPaused;
					break;
				case Keyboard::S:
					shouldShowRays = !shouldShowRays;
					break;
				case Keyboard::E:
					shouldShowSliders = !shouldShowSliders;
					window.setMouseCursorVisible(shouldShowSliders);
					break;
				case Keyboard::N:
					refresh();
					break;
				}
				break;
			}
		}
	};

	refresh();
	while (window.isOpen())
	{
		window.clear(sf::Color(50, 50, 50));
		draw();
		loop();
		events();
		window.display();
	}
	return 0;
}