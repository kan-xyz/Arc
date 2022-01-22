#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																											  //
//  Arc - SFML Vertex Array Utilities																		  //
//  Copyright (C) 2021 - 2022 Kan																					  //
//    																										  //
//  This software is provided 'as-is', without any express or implied warranty.								  //
//  In no event will the authors be held liable for any damages arising from the use of this software.		  //
//																											  //
//  Permission is granted to anyone to use this software for any purpose, including commercial applications,  //
//  and to alter it and redistribute it freely, subject to the following restrictions:						  //
//																											  //
//		1.  The origin of this software must not be misrepresented;											  //
//			you must not claim that you wrote the original software.										  //
//			If you use this software in a product, an acknowledgment										  //
//			in the product documentation would be appreciated but											  //
//			is not required.																				  //
//																											  //
//		2.  Altered source versions must be plainly marked as such,											  //
//			and must not be misrepresented as being the original software.									  //
//																											  //
//		3.  This notice may not be removed or altered from any source distribution.							  //
//																											  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*

	------------------------------------------------------------
			CORE FUNCTIONS
	------------------------------------------------------------
	-	STLRand()

	------------------------------------------------------------
			MEMBER FUNCTIONS
	------------------------------------------------------------
	-	Init()
	-	Seed()
	-	Uniform()
	-	Normal()
	-	PointInLine()
	-	PointInCircle()
	-	PointInRect()
	-	GetGenerator()

	------------------------------------------------------------
			BASIC USAGE
	------------------------------------------------------------

	int main() {
		
		Arc::RNG<std::mt19937> rng;	// create generator. note that ihis is already seeded

		float val = rng.UniformDistribution(0.0f, 1.0f);

	}

*/

#include "Mathematics.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <random>

namespace Arc {

	template <class D, class G, typename ...A>
	typename D::result_type STLRand(G& rng, A&& ...args) {
		D dist(std::forward<A>(args)...);
		return dist(rng);
	}

	template <class G>
	class RandomGenerator {
	public:

		RandomGenerator() : m_rng(std::random_device{}()) {}

		void Init() {
			Seed(std::random_device{}());
		}

		void Seed(const typename G::result_type val = G::default_seed) {
			m_rng.seed(val);
		}

		template <typename T>
		T UniformDistribution(const T minVal, const T maxVal) {
			if constexpr (std::is_same_v<T, sf::Uint8> || std::is_same_v<T, sf::Int8>) {
				return static_cast<T>(Uniform(static_cast<int>(minVal), static_cast<int>(maxVal)));
			}
			else if constexpr (std::is_integral_v<T>) {
				return STLRand<std::uniform_int_distribution<T>>(m_rng, minVal, maxVal);
			}
			else if constexpr (std::is_floating_point_v<T>) {
				return STLRand<std::uniform_real_distribution<T>>(m_rng, minVal, maxVal);
			}
		}

		template <typename T>
		T NormalDistribution(const T mean, const T stddev) {
			return STLRand<std::normal_distribution<T>>(m_rng, mean, stddev);
		}

		G& GetGenerator() {
			return m_rng;
		}

		template <typename T>
		sf::Vector2<T> PointInLine(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
			if constexpr (std::is_integral_v<T>) { return Lerp(a, b, UniformDistribution<float>(0.0f, 1.0f)); }
			else if constexpr (std::is_floating_point_v<T>) { Lerp(a, b, UniformDistribution<T>(0.0, 1.0)); }
		}

		template <typename T>
		sf::Vector2<T> PointInRect(const sf::Rect<T>& rect) {
			if constexpr (std::is_integral_v<T>) {
				return {
					Lerp(rect.left, rect.left + rect.width, UniformDistribution(0.0f, 1.0f)),
					Lerp(rect.top, rect.top + rect.height, UniformDistribution(0.0f, 1.0f))
				};
			}
			else if constexpr (std::is_floating_point_v<T>) {
				return {
					Lerp(rect.left, rect.left + rect.width, UniformDistribution(T{0}, T{1})),
					Lerp(rect.top, rect.top + rect.height, UniformDistribution(T{0}, T{1}))
				};
			}
		}

		template <typename T>
		sf::Vector2<T> PointInCircle(const T minRadius, const T maxRadius, const T minAngle, const T maxAngle) {
			return UniformDistribution(minRadius, maxRadius) * UnitVector(UniformDistribution(minAngle, maxAngle));
		}

		template <typename T>
		T operator () (const T minVal, const T maxVal) { return UniformDistribution(minVal, maxVal); }

	private:
		G m_rng;
	};

	using RNG = RandomGenerator<std::mt19937>;

}
