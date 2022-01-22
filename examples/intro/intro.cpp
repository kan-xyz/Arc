#include "../example_list.hpp"
#include "Arc/Arc.hpp"
#include <SFML/Graphics.hpp>

void ArcDemo::Intro() {

	sf::RenderWindow window({ 800, 600 }, "Intro Demo");
	window.setFramerateLimit(60);

	sf::VertexArray vertices;
	vertices.resize(3 * 3 * 4); // this makes a 3x3 grid of quads (4 vertices)
	vertices.setPrimitiveType(sf::Quads);

	// this creates a 3x3 grid with a cell size of 64x64 positioned at (120, 120) and a padding of (32, 32)
	Arc::MakeGrid(vertices, 0, { 3, 3 }, { 64.0f, 64.0f }, { 120.0f, 120.0f }, { 32.0f, 32.0f });
	Arc::SetVertexArrayColor(vertices, 0, vertices.getVertexCount(), sf::Color::Blue);

	sf::Clock cl;

	while (window.isOpen()) {

		sf::Event evt;
		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) { window.close(); }
		}

		// this will rotate the fourth quad in the grid (starting with index 0) by 60 degrees per second
		Arc::RotateQuad(vertices, 4, cl.restart().asSeconds() * 180.0f);

		window.clear();
		window.draw(vertices);
		window.display();

	}

}
