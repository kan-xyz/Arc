#include "../example_list.hpp"
#include "Arc/Arc.hpp"
#include <SFML/Graphics.hpp>

struct ParticleInfo {
	sf::Vector2f position, velocity, acceleration, size;
	float rotation = 0.0f, rotationSpeed = 0.0f;
	sf::Color color = sf::Color::Green;
	sf::Time lifespan = sf::seconds(1.0f);
};

class Particle {
public:

	Particle() = default;

	void emit(sf::VertexArray& vertices, const std::size_t index, const ParticleInfo& info) {
		Arc::MakeQuad(vertices, index, info.position, info.size);
		Arc::RotateQuad(vertices, index, info.rotation);
		Arc::SetQuadColor(vertices, index, info.color);
		velocity = info.velocity;
		acceleration = info.acceleration;
		rotationSpeed = info.rotationSpeed;
		lifespan = info.lifespan;
	}

	void update(sf::VertexArray& vertices, const std::size_t index, const sf::Time& ts) {
		lifespan -= ts;
		if (lifespan < sf::Time::Zero) {
			Arc::SetQuadColor(vertices, index, sf::Color::Transparent);
			return;
		}
		const float dt = ts.asSeconds();
		velocity += dt * acceleration;
		Arc::MoveQuad(vertices, index, dt * velocity);
		Arc::RotateQuad(vertices, index, dt * rotationSpeed);
	}

	const bool isActive() const {
		return lifespan < sf::Time::Zero;
	}

private:
	sf::Vector2f velocity, acceleration;
	float rotationSpeed = 0.0f;
	sf::Time lifespan;
};

class ParticleSystem {
public:

	ParticleSystem() {
		m_vertices.setPrimitiveType(sf::Quads);
	}

	void resize(const std::size_t size) {
		m_vertices.resize(4 * size); // 4 * size because quads have 4 vertices
		m_particles.resize(size);
		reset();
	}

	void reset() {
		m_index = 0;
		std::fill(m_particles.begin(), m_particles.end(), Particle{});
		Arc::SetVertexArrayColor(m_vertices, 0, m_vertices.getVertexCount(), sf::Color::Transparent);
	}

	void emit(const ParticleInfo& info) {
		m_particles[m_index].emit(m_vertices, m_index, info);
		++m_index;
		if (m_index == m_particles.size()) { m_index = 0; }
	}

	void update(const sf::Time& ts) {
		for (std::size_t i = 0; i < m_particles.size(); ++i) {
			m_particles[i].update(m_vertices, i, ts);
		}
	}

	void draw(sf::RenderTarget& target) {
		target.draw(&m_vertices[0], m_vertices.getVertexCount(), sf::Quads);
	}

private:
	sf::VertexArray m_vertices; // in order to get the most out of batch rendering we need to use vertex arrays
	std::vector<Particle> m_particles;
	std::size_t m_index = 0;
};

void ArcDemo::Particles() {

	std::printf("This is the Arc Particle Demo which shows some batch rendering capabilities of Arc\n");
	std::printf("press Z, X, or C for different particle systems\n");

	sf::RenderWindow window({ 1024, 720 }, "Particles Demo");
	window.setFramerateLimit(60);
	sf::Clock cl;

	Arc::RNG rng;
	ParticleInfo info;
	ParticleSystem system; // all particles will use only one particle system
	system.resize(3000);

	const sf::Time sh1_limit = sf::milliseconds(50);
	sf::Time sh1_timer = sf::Time::Zero;
	float sh1_angle = 0.0f;

	const sf::Time sh2_limit = sf::seconds(0.5f);
	sf::Time sh2_timer = sf::Time::Zero;
	float sh2_angle = 0.0f;

	const sf::Time sh3_limit = sf::seconds(0.3f);
	sf::Time sh3_timer;

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) { window.close(); }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }

		const sf::Vector2f mPos = sf::Vector2f(sf::Mouse::getPosition(window));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && (sh1_timer > sh1_limit)) {
			info.position = mPos;
			info.size = { 30.0f, 10.0f };
			info.color = sf::Color::Green;
			info.lifespan = sf::seconds(3.0f);
			const float inc = (1.0f / 10.0f) * (2.0f * Arc::Pi_v<float>);
			const float maxA = sh1_angle + (2.0f * Arc::Pi_v<float>);
			for (float a = sh1_angle; a < maxA; a += inc) {
				const float deg = Arc::Degrees(a);
				info.velocity = 200.0f * Arc::UnitVector(deg);
				info.acceleration = 800.0f * Arc::UnitVector(deg);
				info.rotation = deg;
				system.emit(info);
			}
			sh1_angle += 0.2f;
			sh1_timer = sf::Time::Zero;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && (sh2_timer > sh2_limit)) {
			sh2_angle = rng(0.0f, 360.0f);
			info.position = mPos;
			info.size = { 30.0f, 30.0f };
			info.color = sf::Color::Yellow;
			info.lifespan = sf::seconds(3.0f);
			const float inc = (1.0f / 60.0f) * (2.0f * Arc::Pi_v<float>);
			const float maxA = sh2_angle + (2.0f * Arc::Pi_v<float>);
			for (float a = sh2_angle; a < maxA; a += inc) {
				const float deg = Arc::Degrees(a);
				info.velocity = 300.0f * Arc::UnitVector(deg);
				info.acceleration = 400.0f * Arc::UnitVector(deg);
				info.rotation = deg;
				system.emit(info);
			}
			sh2_timer = sf::Time::Zero;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && (sh3_timer > sh3_limit)) {
			const float angle = rng(0.0f, 360.0f);
			info.position = mPos;
			info.size = { 10.0f, 50.0f };
			info.color = sf::Color::Cyan;
			info.lifespan = sf::seconds(3.0f);
			const float inc = (1.0f / 20.0f) * (2.0f * Arc::Pi_v<float>);
			const float maxA = angle + (2.0f * Arc::Pi_v<float>);
			for (float a = angle; a < maxA; a += inc) {
				float vel = 100.0f;
				for (int i = 0; i < 5; ++i) {
					const float deg = Arc::Degrees(a);
					info.velocity = vel * Arc::UnitVector(deg);
					info.acceleration = 400.0f * Arc::UnitVector(deg);
					info.rotation = deg;
					system.emit(info);
					vel += 100.0f;
				}
			}
			sh3_timer = sf::Time::Zero;
		}

		const sf::Time dt = cl.restart();
		sh1_timer += dt;
		sh2_timer += dt;
		sh3_timer += dt;

		system.update(dt);

		window.clear();
		system.draw(window);
		window.display();
	}

}
