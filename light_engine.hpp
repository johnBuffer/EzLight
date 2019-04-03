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
		
	}

	const sf::Texture& texture() const
	{
		return m_final_texture.getTexture();
	}

private:
	sf::RenderTexture m_final_texture;
	sf::RenderTexture m_light_texture;

	Blur m_blur;

	fva::SwapArray<LightSource> m_lights;
	fva::SwapArray<up::Segment> m_casters;

	void renderLight(const LightSource& source)
	{
		m_light_texture.clear();

		
	}

	void addCasterShadow(const LightSource& source, const up::Segment& segment, sf::VertexArray& va)
	{

	}
};