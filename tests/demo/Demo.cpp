#include "Demo.h"

#include <Arc/Arc.hpp>
#include <SFML/Graphics.hpp>

void Demo::Demo()
{
    sf::RenderWindow window({ 800, 600 }, "Arc Demo");
    window.setFramerateLimit(60);

    sf::VertexArray vertices(sf::Quads, 4);
    Arc::MakeQuad(vertices, 0, { 400.0f, 300.0f }, { 256.0f, 256.0f });

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

        const float dt = cl.restart().asSeconds();
        Arc::RotateQuad(vertices, 0, dt * 60.0f);

        window.clear();
        window.draw(vertices);
        window.display();
    }
}
