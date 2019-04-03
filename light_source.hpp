#pragma once

#include "vec2.h"
#include <SFML/Graphics.hpp>

struct LightSource
{
	up::Vec2 position;
	float radius;
	sf::Color color;
};
