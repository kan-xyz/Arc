# Arc

Arc is a header only utility library for SFML whose main focus is on vertex arrays.  

This is a fully templated library which means that all you have to do is include  
this in your project and you can use it right away.

**Note:**  
This library makes use of C++17 features so that means you have to use  
C++17 or higher.

## Sample Code
```
#include <Arc/Arc.hpp> // include all of Arc's features
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window({ 800, 600 }, "Demo");
    window.setFramerateLimit(60);
    
    sf::VertexArray vertices;
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(4);
    
    Arc::MakeQuad(vertices, 0, { 400.0f, 300.0f }, { 200.0f, 200.0f });
    
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event evt;
        while (window.pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        const float dt = clock.restart.asSeconds();
        Arc::RotateQuad(vertices, 0, dt * 180.0f); // rotate the quad 180 degrees per second
        
        window.clear();
        window.draw(vertices);
        window.display();
    }
    
    return 0;
}
```

Even though the primary focus is vertex arrays, there are some more features that you can also
find in this library such as vector math and angle conversions. I may also be including more features as well.  

## Building the Examples
This library comes wth examples that can be built using the command prompt and cmake. Just set ARC_SFML_INCLUDE_DIR
and ARC_SFML_LIB_DIR to the appropriate locations before building them.

Please note that at the moment, building the examples with static linking only works for windows.
