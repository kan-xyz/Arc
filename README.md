# Arc Library 
Arc is a templated header only utility library for SFML. Since it is a header only library all you need  
to do is just include the library into your project and you can use it right away.  

Please note that this library uses C++ 17 features which means that C++ 17 and above is required.  

## Features
Arc's current features:
- Vertex Array Utilities: Functions designed for manipulating SFML vertex arrays.  
- Mathematics: Common math functions for use in SFML.  
- Random: A random number generator which is a thin wrapper over C++ random.  
- Resource Manager: A class that handles management of SFML resources such as `sf::Texture`.  
- Texture Atlas: A class to render other textures onto one large texture. It is used to place multiple textures under one vertex array.  

## Example Code
The code below draws a 3x3 grid with the center quad rotating about its center.  
```
#include "Arc/Arc.hpp" // include all of Arc's features
#include <SFML/Graphics.hpp>

int main() {

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
		Arc::RotateQuad(vertices, 4, cl.restart().asSeconds() * 60.0f);

		window.clear();
		window.draw(vertices);
		window.display();

	}
	return 0;
}
```

## Building the Examples
There are two ways to view the examples. One is to build them using cmake and the other is to just add the source files to your project  
as is demonstrated below
```
#include "example_list.hpp" // this is where you can find all the available demos

int main() {
	ArcDemo::ExampleName(); // all examples are in the ArcDemo namespace
	return 0;
}
```
