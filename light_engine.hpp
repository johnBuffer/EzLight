#pragma once
#include "dynamic_blur.hpp"
#include "light_source.hpp"
#include "fast_array.hpp"

class LigthEngine
{
public:
	LigthEngine(uint32_t width, uint32_t height) :
		m_blur(width, height)
	{
		m_final_texture.create(width, height);
		m_light_texture.create(width, height);
	}

	void render()
	{
		m_final_texture.clear();
		for (const LightSource& source : m_lights)
		{
			renderShadows(source);
			m_final_texture.draw(sf::Sprite(m_light_texture.getTexture()), sf::BlendAdd);
		}
		m_final_texture.display();
	}

	const sf::Texture& texture() const
	{
		return m_blur.apply(m_final_texture.getTexture(), 3);
	}

	void addLight(const LightSource& source)
	{
		m_lights.add(source);
	}

	void addCaster(const up::Segment& segment)
	{
		m_casters.add(segment);
	}

private:
	sf::RenderTexture m_final_texture;
	sf::RenderTexture m_light_texture;

	mutable Blur m_blur;

	fva::SwapArray<LightSource> m_lights;
	fva::SwapArray<up::Segment> m_casters;

	void renderLight(const LightSource& source)
	{
		constexpr float PI(3.141592653f);
		constexpr uint32_t point_count(32);

		sf::VertexArray va(sf::TriangleFan, point_count);
		va[0].position = sf::Vector2f(source.position->x, source.position->y);
		va[0].color = sf::Color::White;

		for (uint32_t i(0); i < point_count - 1; ++i)
		{
			float angle(i*2.0f*PI / float(point_count-2));
			float x(source.position->x + source.radius * cos(angle));
			float y(source.position->y + source.radius * sin(angle));
			
			va[i+1].position = sf::Vector2f(x, y);
			va[i+1].color = sf::Color(0, 0, 0, 0);
		}

		m_light_texture.draw(va);
	}

	void renderShadows(const LightSource& source)
	{
		m_light_texture.clear();
		sf::VertexArray va(sf::Quads, 0);
		renderLight(source);

		for (const up::Segment& segment : m_casters)
		{
			addCasterShadow(source, segment, va);
		}

		m_light_texture.draw(va);
		m_light_texture.display();
	}

	void addCasterShadow(const LightSource& source, const up::Segment& segment, sf::VertexArray& va)
	{
		const up::Vec2& center(*source.position);
		const up::Vec2& p1(segment.p1);
		const up::Vec2& p2(segment.p2);

		up::Vec2 cp1(p1 - center);
		up::Vec2 cp2(p2 - center);
		cp1.normalize();
		cp2.normalize();

		const up::Vec2& p3(p1 + source.radius * cp1);
		const up::Vec2& p4(p2 + source.radius * cp2);

		const sf::Vertex v1(sf::Vector2f(p1.x, p1.y), sf::Color::Black, sf::Vector2f());
		const sf::Vertex v2(sf::Vector2f(p3.x, p3.y), sf::Color::Black, sf::Vector2f());
		const sf::Vertex v3(sf::Vector2f(p4.x, p4.y), sf::Color::Black, sf::Vector2f());
		const sf::Vertex v4(sf::Vector2f(p2.x, p2.y), sf::Color::Black, sf::Vector2f());

		va.append(v1);
		va.append(v2);
		va.append(v3);
		va.append(v4);
	}
};