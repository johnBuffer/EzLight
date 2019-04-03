#include <SFML/Graphics.hpp>
#include "light_engine.hpp"

int main()
{
	const uint32_t width(1600);
	const uint32_t height(900);

	sf::RenderWindow window(sf::VideoMode(width, height), "Light");
	window.setVerticalSyncEnabled(true);

	LigthEngine engine(width, height);

	engine.addLight(LightSource(up::Vec2(800, 0), 1600.0f));
	engine.addCaster(up::Segment(up::Vec2(700, 400), up::Vec2(900, 400)));
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		engine.render();
		sf::Sprite lights_sprite(engine.texture());

		window.clear();

		window.draw(lights_sprite, sf::BlendAdd);

		window.display();
	}

	return 0;
}