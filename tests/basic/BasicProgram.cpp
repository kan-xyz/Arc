#include "BasicProgram.h"

#include "Arc/Arc.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <array>

// struct is here for demonstration purposes
struct Quad
{
    // this function uses modular arithmetic to ensure that the index always sits between 0 and 3 inclusive
    sf::Vertex& operator [] (std::size_t index) { return vertices[index % 4]; }
    const sf::Vertex& operator [] (std::size_t index) const { return vertices[index % 4]; }

    sf::Vertex vertices[4];
};

void Demo::BasicProgram()
{
    printf("\nWelcome to the Arc Library\nThis is a basic program to see how to use Arc\n");

    sf::RenderWindow window({ 800, 600 }, "Basic Program");
    window.setFramerateLimit(60);
    
    // the main features of Arc works on vertex arrays
    sf::VertexArray vertices_sfml = sf::VertexArray(sf::Quads, 4); // vertex array
    std::vector<sf::Vertex> vertices_vector(4); // a vector of vertices with size = 4
    std::array<sf::Vertex, 4> vertices_array;
    sf::Vertex vertices_cstyle[4];
    sf::Vertex* vertices_heap = new sf::Vertex[4 * 3 * 3]; // making a 3 x 3 grid with this
    
    // your own classes can also be used here as long
    // as they have defined the array index operator []
    Quad quad;

    // Below here are basic function that can be used in Arc
    // The basic syntax of the Arc Quad functions is:
    //
    // Arc::FuncName(vertex_array, quan_index, ...);
    //
    // these functions are templated on the data structure
    // that contains the vertices

    // this makes a quad using the first four vertices at center = { 200, 200 } and size = { 32, 32 }
    Arc::MakeQuad(vertices_sfml, 0, { 200.0f, 200.0f }, { 32.0f, 32.0f });
    Arc::SetQuadColor(vertices_sfml, 0, sf::Color::White);

    // this makes a rectangle using sf::FloatRect
    Arc::MakeRect(vertices_vector, 0, { 10.0f, 10.0f, 32.0f, 32.0f });
    Arc::SetQuadColor(vertices_vector, 0, sf::Color::Magenta);

    // since these functions are templated on the container of the vertices
    // c++ and c style arrays can be used here as well
    Arc::MakeQuad(vertices_array, 0, { 500.0f, 500.0f }, { 100.0f, 100.0f }); // c++
    Arc::SetQuadColor(vertices_array, 0, sf::Color::Green); // c++
    Arc::MakeQuad(vertices_cstyle, 0, { 100.0f, 500.0f }, { 64.0f, 64.0f }); // c
    Arc::SetQuadColor(vertices_cstyle, 0, sf::Color::Cyan); // c

    // functions like this also exist
    // the syntax is:
    //
    // Arc::MakeGrid(vertex_array, start_quad, grid_size, cell_size, position, cell_padding);
    //
    Arc::MakeGrid(vertices_heap, 0, { 3, 3 }, { 32.0f, 32.0f }, { 10.0f, 200.0f }, { 5.0f, 5.0f });

    // syntax of this functions like this are
    //
    // Arc::FuncName(vertex_array, start_index, count_of_indeces, ...);
    //
    Arc::SetVertexArrayColor(vertices_heap, 0, 4 * 3 * 3, sf::Color::Yellow);

    // your own classes can be used as well as long as the necessary functions are provided
    Arc::MakeQuad(quad, 0, { 300.0f, 200.0f }, { 32.0f, 32.0f });
    Arc::SetQuadColor(quad, 0, sf::Color::Red);

    // functions like these manipulate quads
    Arc::RotateQuad(vertices_cstyle, 0, 20.0f); // in degrees
    Arc::RotateQuad(vertices_heap, 4, 45.0f);
    Arc::ScaleQuad(quad, 0, { 5.0f, 2.0f });

    float t = 0.0f;

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

        const float dt = cl.restart().asSeconds();

        // continuous rotation
        Arc::RotateQuad(vertices_heap, 4, dt * 180.0f);

        // somethig fancy
        t += dt;
        Arc::SetQuadPosition(vertices_array, 0, { 500.0f, 300.0f + 200.0f * std::sin(t) });
        Arc::RotateQuad(vertices_array, 0, dt * 45.0f);

        window.clear();
        window.draw(vertices_sfml);
        window.draw(vertices_vector.data(), 4, sf::Quads);
        window.draw(vertices_array.data(), 4, sf::Quads);
        window.draw(&vertices_cstyle[0], 4, sf::Quads);
        window.draw(vertices_heap, 4 * 3 * 3, sf::Quads);
        window.draw(&quad.vertices[0], 4, sf::Quads);
        window.display();
    }

    delete[] vertices_heap;
}
