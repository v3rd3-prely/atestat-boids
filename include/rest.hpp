#pragma once

#include <SFML/System.hpp>

#define BORDER true
#define N_MAX 300
#define A_MAX 6+(4*BORDER)
#define R_MAX 21
#define FOV 230.f
#define SEPARATION 2.f
#define COHESION 1.f
#define ALIGNMENT 0.1f
#define PERCEPTION 0.0015f
#define PI 3.14159265359

float dist(const sf::Vector2f& a, const sf::Vector2f& b = sf::Vector2f(0, 0));
int random(int const &mi, int const &ma);