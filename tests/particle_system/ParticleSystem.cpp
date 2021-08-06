#include "ParticleSystem.h"
#include <Arc/QuadUtils.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <random>

namespace Demo
{

    // this defines the basic data
    // for a basic particle
    struct Particle
    {
        sf::Vector2f velocity, acceleration;
        float rotationSpeed = 0.0f, rotationAcceleration = 0.0f;
        sf::Time lifespan = sf::Time::Zero;
        bool isActive = false;
    };

    // the details of the mechanics are laid out in comments
    class ParticleSystem
    {
    public:

        ParticleSystem() = default;

        // this is where we give the max number of particles
        void resize(const std::size_t size)
        {
            m_vertices.resize(4 * size); // this needs to have that 4 because quads have 4 vertices
            m_particleData.resize(size);
        }

        void emit(const sf::RenderWindow& window, std::mt19937& rng)
        {
            if (m_particleData[m_index].isActive == false)
            {
                std::uniform_real_distribution<float> randVelocity(100.0f, 300.0f);
                std::uniform_real_distribution<float> randAcceleration(200.0f, 600.0f);
                std::uniform_real_distribution<float> randAngle(0.0f, 360.0f);
                std::uniform_real_distribution<float> randRotationSpeed(-60.0f, 60.0f);
                std::uniform_real_distribution<float> randRotationAcceleration(-60.0f, 60.0f);
                std::uniform_real_distribution<float> randLifespan(3.0f, 6.0f);
                std::uniform_int_distribution<int> randColor(0, 255); // this is int because C++ does not have a specialization
                                                                      // for std::uniform_int_distribution<sf::Uint8>

                // basic properties of the particles
                float rotation = randAngle(rng);
                float omega = randRotationSpeed(rng);
                float alpha = randRotationAcceleration(rng);
                float speed = randVelocity(rng);
                sf::Color color = {
                    static_cast<sf::Uint8>(randColor(rng)),
                    static_cast<sf::Uint8>(randColor(rng)),
                    static_cast<sf::Uint8>(randColor(rng)),
                    255
                };

                // below here is where we can see the basic usage of Arc's vertexArray utils.
                // the first parameter is the vertex array and the second is the quad index
                // note that Arc also has a shortcut function for this in the form of:
                //
                // Arc::MakeQuad(vertexArray, index, position, size, rotation, color, textureRect);
                //
                // there are also other functions such as:
                //
                // Arc::SetTextureRect(...);
                // Arc::SetSize(...);
                // Arc::SetPosition(...);
                //
                // among others
                //
                Arc::MakeQuad(m_vertices, m_index, sf::Vector2f(sf::Mouse::getPosition(window)), { 32.0f, 32.0f });
                Arc::RotateQuad(m_vertices, m_index, rotation);
                Arc::SetQuadColor(m_vertices, m_index, color);

                float theta1 = randAngle(rng);
                float theta2 = randAngle(rng);

                // other particle data
                m_particleData[m_index].velocity = randVelocity(rng) * sf::Vector2f(std::cos(theta1), std::sin(theta1));
                m_particleData[m_index].acceleration = randAcceleration(rng) * sf::Vector2f(std::cos(theta2), std::sin(theta2));
                m_particleData[m_index].rotationSpeed = randRotationSpeed(rng);
                m_particleData[m_index].rotationAcceleration = randRotationAcceleration(rng);
                m_particleData[m_index].lifespan = sf::seconds(randLifespan(rng));
                m_particleData[m_index].isActive = true;

                m_index = ++m_index % m_particleData.size();
            }
        }

        void update(const sf::Time& timestep)
        {
            const float dt = timestep.asSeconds();

            for (std::size_t i = 0; i < m_particleData.size(); ++i)
            {
                if (m_particleData[i].isActive == false)
                {
                    continue;
                }

                m_particleData[i].lifespan -= timestep;
                if (m_particleData[i].lifespan < sf::Time::Zero)
                {
                    // make the quad invisible
                    Arc::SetQuadColor(m_vertices, i, sf::Color::Transparent);
                    m_particleData[i].isActive = false;
                    continue;
                }

                m_particleData[i].velocity += dt * m_particleData[i].acceleration;
                m_particleData[i].rotationSpeed += dt * m_particleData[i].rotationAcceleration;

                // here are some basic quad operations
                // other operations include
                //
                // Arc::TransformQuad(...);
                // Arc::SetQuadAngle(...)
                // 
                // you can explore the arc header file
                // to find out what els Arc can do
                Arc::MoveQuad(m_vertices, i, dt * m_particleData[i].velocity);
                Arc::RotateQuad(m_vertices, i, dt * m_particleData[i].rotationSpeed);
            }
        }

        void draw(sf::RenderWindow& window)
        {
            window.draw(m_vertices.data(), m_vertices.size(), sf::Quads);
        }

    private:
        std::vector<sf::Vertex> m_vertices; // this is where we store the vertices for the particles
                                            // in order to get the full benefit of batch rendering we need
                                            // to place everything in one vertex array
        std::vector<Particle> m_particleData;
        std::size_t m_index = 0;
    };

    void ParticleSystemDemo()
    {
        printf("\nThis is the Arc Particle System Demo\nJust press the left mouse button to generate some particles\n");

        sf::RenderWindow window({ 800, 600 }, "Particle System");
        window.setFramerateLimit(60);

        std::mt19937 rng(std::random_device{}());
        ParticleSystem particleSystem;
        particleSystem.resize(1000);

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                particleSystem.emit(window, rng);
            }

            particleSystem.update(cl.restart());

            window.clear();
            particleSystem.draw(window);
            window.display();
        }
    }

}
