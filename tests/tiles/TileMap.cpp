#include "TileMap.h"
#include <Arc/QuadUtils.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/VertexArray.hpp>

namespace Demo
{

    void TileMapDemo()
    {
        printf("\nThis is the Arc TileMap Demo\nPress the arrow keys to change the padding between cells\n");
        sf::RenderWindow window({ 800, 600 }, "Tile Map");
        window.setFramerateLimit(60);

        sf::Vector2u gridSize = { 10, 10 };
        sf::Vector2f cellSize = { 32.0f, 32.0f };
        sf::Vector2f padding;
        float paddingAdder = 0.1f;

        sf::VertexArray vertices(sf::Quads, 4 * 10 * 10);

        // the pattern for functions like this is that
        // the vertex array is always the first parameter
        // the start vertex is the second parameter
        // the count of vertices is the third parameter
        Arc::SetVertexArrayColor(vertices, 0, 4 * 10 * 10, sf::Color::Magenta);

        sf::Clock cl;
        while (window.isOpen())
        {
            sf::Event e;
            while (window.pollEvent(e))
            {
                if (e.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { padding.x -= paddingAdder; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { padding.x += paddingAdder; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { padding.y -= paddingAdder; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { padding.y += paddingAdder; }

            // this is used to make grids of any size, any position and with
            // any spacing between them
            //
            // this function manually uses:
            //
            // Arc::MakeRect(...);
            //
            Arc::MakeGrid(vertices, 0, gridSize, cellSize, padding, padding);

            window.clear();
            window.draw(vertices);
            window.display();
        }
    }

}
