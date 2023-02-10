#include <SFML/Graphics.hpp>
#include <ctime>

#include "fps.hpp"
#include "boid.hpp"
#include "wall.hpp"
#include "ray.hpp"
#include "slider.hpp"
#include "rest.hpp"

using namespace sf;

int main()
{
	float separation, cohesion, alignment, perception;
	bool isPaused = true, showRays = true;
	float deltaT = 0;
	
	RenderWindow window(VideoMode(1024, 576), "Boids", Style::Fullscreen);
	Boid boids[N_MAX];
	Wall walls[A_MAX];
	Event event;
	FPS timer;
	Slider
	sep( 10, window.getSize().y- 75, "Separation"),
	coh(350, window.getSize().y- 75,   "Cohesion"),
	ali( 10, window.getSize().y-150, "Alignement"),
	per(350, window.getSize().y-150, "Perception");

	bool infoToggle = false;
	bool tabPressed;
	Clock cooldown;
	Font infoFont;
	Text infoText;
	infoFont.loadFromFile("../fonts/arial.ttf");
	infoText.setFont(infoFont);
	infoText.setOutlineColor(Color(0, 0, 0));
	infoText.setOutlineThickness(4);
	infoText.setString(" Press Space to pause\n Press S to show rays\n Press N to reset boids\n Press Esc to exit");
	infoText.setPosition(0, 0);


	srand(time(NULL));
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(true);

	// LOOP

	auto loop = [&](){
		sep.check(window);
		coh.check(window);
		ali.check(window);
		per.check(window);

		separation = sep.value*SEPARATION;
		cohesion = coh.value*COHESION;
		alignment = ali.value*ALIGNMENT;
		perception = per.value*per.value*PERCEPTION;

		for(Boid &boid : boids)
		{
			boid.think(boids, separation, cohesion, alignment, perception);
			boid.avoid(walls, A_MAX);
			boid.contain(window.getSize().x, window.getSize().y);
			boid.update(deltaT, perception);
			boid.show(window, showRays);
		}
		for(Wall &wall : walls)
		{
			wall.show(window);
		}
		
		sep.show(window);
		coh.show(window);
		ali.show(window);
		per.show(window);
		
		if(infoToggle)
			window.draw(infoText);
		if(Keyboard::isKeyPressed(Keyboard::Tab))
		{
			tabPressed = true;
		}
		if(cooldown.getElapsedTime().asMilliseconds() > 50)
		{
			infoToggle = tabPressed;
			
			tabPressed = false;
			cooldown.restart();
		}
	};

	// RESET EVERYTHING

	auto reset = [&](){
		walls[0] = Wall(Vector2f(0, 0), Vector2f(window.getSize().x, 0));
		walls[1] = Wall(Vector2f(window.getSize().x, 0), Vector2f(window.getSize().x, window.getSize().y));
		walls[2] = Wall(Vector2f(window.getSize().x, window.getSize().y), Vector2f(0, window.getSize().y));
		walls[3] = Wall(Vector2f(0, window.getSize().y), Vector2f(0, 0));
		for(int i = 4; i < A_MAX; i++)
		{
			float rx1 = random(0, window.getSize().x);
			float ry1 = random(0, window.getSize().y);
			float rx2 = random(-400, 400);
			float ry2 = random(-400, 400);
			walls[i] = Wall(Vector2f(rx1, ry1), Vector2f(rx1+rx2, ry1+ry2));
		}

		for(Boid &boid : boids)
		{
			boid.pos = Vector2f(random(0, window.getSize().x), random(0, window.getSize().y));
			boid.speed = Vector2f(random(-500, 500), random(-500, 500));
		}
	};

	// EVENTS

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
					showRays = !showRays;
					break;
				case Keyboard::N:
					reset();
					break;
				}
				break;
			}
		}
	};

	reset();
	while (window.isOpen())
	{
		window.clear();
		timer.update();
		deltaT = timer.getDeltaT()*!isPaused;
		loop();
		events();
		window.display();
	}
	return 0;
}