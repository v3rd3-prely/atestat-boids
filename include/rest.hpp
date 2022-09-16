#pragma once

#include <SFML/System.hpp>

#define N_MAX 200
#define A_MAX 8
#define R_MAX 21
#define FOV 230.f
#define PI 3.14159265359
#define SEPARATION 10.f
#define COHESION 1.f
#define ALIGNMENT 0.05f
#define PERCEPTION 0.05f


float dist(sf::Vector2f a, sf::Vector2f b = sf::Vector2f(0, 0));
int random(int const &mi, int const &ma);