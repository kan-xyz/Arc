#include "../example_list.hpp"
#include "Arc/Arc.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace ArcDemo {

	void Random() {

		sf::RenderWindow window({ 1024, 720 }, "random number generator demo");
		window.setFramerateLimit(30);

		Arc::ResourceManager<std::string, sf::Font> fonts;
		fonts.AddFile("vt323", "resources/PressStart2P-Regular.ttf");
		
		if (fonts.LoadResource("vt323") == nullptr) {
			std::cout << "error: the reason you are getting this message is because some resources that are needed by the application are not presesnt in the expected directory. if you see this message, make sure that the \"resources\" folder is in the same directory as the application. you can find this folder in the same location as the source code\n\n";
			std::cout << "press any key to exit the application\n\n";
			std::cin.get();
			return;
		}

		const unsigned int fontsize = 16;

		Arc::RNG rng; // this thing is automatically seeded when it is declared
		const double unif_a = 0.0f, unif_b = 1.0f;
		const double norm_mean = 10.0f, norm_stddev = 2.0f;
		const double bern_rate = 0.8f;
		const double weib_shape = 1.0f, weib_scale = 0.1f;

		sf::Text intro, uniform, normal, bernoulli, weibull;

		intro = sf::Text("press space to generate new random numbers", fonts.GetResource("vt323"), fontsize);

		uniform = sf::Text("uniform distribution (a=" + std::to_string(unif_a) + ",b=" + std::to_string(unif_b) + "): " + std::to_string(rng(unif_a, unif_b)), fonts.GetResource("vt323"), fontsize);
		uniform.setPosition({ 0.0f, 60.0f });

		normal = sf::Text("normal distribution (mean=" + std::to_string(norm_mean) + ",stddev=" + std::to_string(norm_stddev) + "): " + std::to_string(rng.NormalDistribution(norm_mean, norm_stddev)), fonts.GetResource("vt323"), fontsize);
		normal.setPosition({ 0.0f, 120.0f });

		bernoulli = sf::Text("bernoulli distribution (success rate=" + std::to_string(bern_rate) + "): " + std::to_string(Arc::STLRand<std::bernoulli_distribution>(rng.GetGenerator(), bern_rate)), fonts.GetResource("vt323"), fontsize);
		bernoulli.setPosition({ 0.0f, 180.0f });

		weibull = sf::Text("weibull distribution (shape=" + std::to_string(weib_shape) + ",scale=" + std::to_string(weib_scale) + "): " + std::to_string(Arc::STLRand<std::weibull_distribution<double>>(rng.GetGenerator(), weib_shape, weib_scale)), fonts.GetResource("vt323"), fontsize);
		weibull.setPosition({ 0.0f, 240.0f });

		while (window.isOpen()) {

			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == sf::Event::Closed) { window.close(); }
				if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) {
					const double unif = rng(unif_a, unif_b);
					const double norm = rng.NormalDistribution(norm_mean, norm_stddev);
					const bool bern = Arc::STLRand<std::bernoulli_distribution>(rng.GetGenerator(), bern_rate);
					const double weib = Arc::STLRand<std::weibull_distribution<double>>(rng.GetGenerator(), weib_scale, weib_shape);
					uniform.setString("uniform distribution (a=" + std::to_string(unif_a) + ",b=" + std::to_string(unif_b) + "): " + std::to_string(unif));
					normal.setString("normal distribution (mean=" + std::to_string(norm_mean) + ",stddev=" + std::to_string(norm_stddev) + "): " + std::to_string(norm));
					bernoulli.setString("bernoulli distribution (success rate=" + std::to_string(bern_rate) + "): " + std::to_string(bern));
					weibull.setString("weibull distribution (shape=" + std::to_string(weib_shape) + ",scale=" + std::to_string(weib_scale) + "): " + std::to_string(weib));
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }

			window.clear();
			window.draw(intro);
			window.draw(uniform);
			window.draw(normal);
			window.draw(bernoulli);
			window.draw(weibull);
			window.display();

		}

	}

}
