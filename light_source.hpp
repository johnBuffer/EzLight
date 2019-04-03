#pragma once

#include "vec2.h"
#include <SFML/Graphics.hpp>

struct LightSource
{
	LightSource() :
		position(),
		radius(0.0f),
		color(sf::Color::White)
	{}

	LightSource(const up::Vec2& pos, float r) :
		position(&pos),
		radius(r),
		color(sf::Color::White)
	{}

	const up::Vec2* position;
	float radius;
	sf::Color color;
};
