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
			TRIGONOMETRY
	------------------------------------------------------------
		-	Pi()
		-	Degrees()
		-	Radians()

	------------------------------------------------------------
			POINT TRANSFORMS
	------------------------------------------------------------
		-	RotatePoint()
		-	ScalePoint()
		-	TransformPoint()
		-	ShearPoint()
		-	ReflectPointAlongX()
		-	ReflectPointAlongY()

	------------------------------------------------------------
			LERP
	------------------------------------------------------------
		-	Lerp()
		-	CosineLerp()
		-	Oscillate()

	------------------------------------------------------------
			SPLINE
	------------------------------------------------------------
		-	CubicBezierSpline()

	------------------------------------------------------------
			VECTOR OPERATIONS
	------------------------------------------------------------
		-	GetVectorLength()
		-	GetVectorAngle()
		-	UnitVector()
		-	GetUnitVector()
		-	GetDotProduct()
		-	GetCrossProduct()

*/

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <type_traits>

namespace Arc {

	//////////////////////////////////////////////////////////////////////
	//	TRIGONOMETRY
	//////////////////////////////////////////////////////////////////////

	template <typename T> inline constexpr T Pi_v = static_cast<T>(3.14159265358979323846264338327950288);

	template <typename F>
	F Degrees(const F radians) {
		return (static_cast<F>(180) / Pi_v<F>) * radians;
	}

	template <typename F>
	F Radians(const F degrees) {
		return (Pi_v<F> / static_cast<F>(180)) * degrees;
	}

	//////////////////////////////////////////////////////////////////////
	//	POINT TRANSFORMS
	//////////////////////////////////////////////////////////////////////

	template <typename F>
	void RotatePoint(sf::Vector2<F>& point, const F sin, const F cos, const sf::Vector2<F>& center = {}) {
		point = { (point.x - center.x) * cos - (point.y - center.y) * sin + center.x, (point.x - center.x) * sin + (point.y - center.y) * cos + center.y };
	}

	template <typename F>
	void ScalePoint(sf::Vector2<F>& point, const sf::Vector2<F>& scaleFactor, const sf::Vector2<F>& center = {}) {
		point = { (point.x - center.x) * scaleFactor.x + center.x, (point.y - center.y) * scaleFactor.y + center.y };
	}

	template <typename F>
	void TransformPoint(sf::Vector2<F>& point, const sf::Vector2<F>& translation, const F sin, const F cos, const sf::Vector2<F>& scaleFactor, const sf::Vector2<F>& center = {}) {
		point = { scaleFactor.x * ((point.x - center.x) * cos - (point.y - center.y) * sin) + translation.x + center.x, scaleFactor.y * ((point.x - center.x) * sin + (point.y - center.y) * cos) + translation.y + center.y };
	}

	template <typename F>
	void ShearPoint(sf::Vector2<F>& point, const sf::Vector2<F>& shearFactor, const sf::Vector2<F>& center = {}) {
		point = { (static_cast<F>(1) + shearFactor.x * shearFactor.y) * (point.x - center.x) + shearFactor.y * (point.y - center.y) + center.x, shearFactor.x * (point.x - center.x) + point.y };
	}

	template <typename F>
	void ReflectPointAlongX(sf::Vector2<F>& point, const sf::Vector2<F>& center = {}) {
		point.y = -point.y + static_cast<F>(2) * center.y;
	}

	template <typename F>
	void ReflectPointAlongY(sf::Vector2<F>& point, const sf::Vector2<F>& center = {}) {
		point.x = -point.x + static_cast<F>(2) * center.x;
	}

	//////////////////////////////////////////////////////////////////////
	//	LERP
	//////////////////////////////////////////////////////////////////////

	template <typename T, typename F>
	T Lerp(const T start, const T end, const F t) {
		static_assert(std::is_floating_point_v<F>, "t must be a floating point type");
		if constexpr (std::is_same_v<T, F>) {
			return start * (static_cast<F>(1) - t) + end * t;
		}
		else if constexpr (std::is_integral_v<T>) {
			return static_cast<T>(Lerp(static_cast<F>(start), static_cast<F>(end), t));
		}
		else if constexpr (std::is_floating_point_v<T>) {
			static_assert(sizeof(T) <= sizeof(F), "F must be of a higher precision than T");
			return static_cast<T>(Lerp(static_cast<F>(start), static_cast<F>(end), t));
		}
	}

	template <typename T, typename F>
	sf::Vector2<T> Lerp(const sf::Vector2<T>& start, const sf::Vector2<T>& end, const F t) {
		return { Lerp(start.x, end.x, t), Lerp(start.y, end.y, t) };
	}

	template <typename F>
	sf::Color Lerp(const sf::Color& start, const sf::Color& end, const F t) {
		return { Lerp(start.r, end.r, t), Lerp(start.g, end.g, t), Lerp(start.b, end.b, t), Lerp(start.a, end.a, t) };
	}

	template <typename T, typename F>
	T CosineLerp(const T start, const T end, const F t) {
		return Lerp(start, end, static_cast<F>(0.5) * (static_cast<F>(1) - std::cos(Pi_v<F> * t)));
	}

	template <typename T, typename F>
	T Oscillate(const T minVal, const T maxVal, const F frequency, const F phase, const F t) {
		return Lerp(minVal, maxVal, static_cast<F>(0.5) * (static_cast<F>(1) - std::cos(static_cast<F>(2) * Pi_v<F> * frequency * t + phase)));
	}

	//////////////////////////////////////////////////////////////////////
	//	SPLINE
	//////////////////////////////////////////////////////////////////////

	template <typename T, typename F>
	sf::Vector2<T> CubicBezierSpline(const sf::Vector2<T>& start, const sf::Vector2<T>& ctrl1, const sf::Vector2<T>& ctrl2, const sf::Vector2<T>& end, const F t) {
		const sf::Vector2<T> a0 = Lerp(start, ctrl1, t);
		const sf::Vector2<T> a1 = Lerp(ctrl1, ctrl2, t);
		const sf::Vector2<T> a2 = Lerp(ctrl2, end, t);
		const sf::Vector2<T> b0 = Lerp(a0, a1, t);
		const sf::Vector2<T> b1 = Lerp(a1, a2, t);
		return Lerp(b0, b1, t);
	}

	//////////////////////////////////////////////////////////////////////
	//	VECTOR OPERATIONS
	//////////////////////////////////////////////////////////////////////

	template <typename F>
	F GetVectorLength(const sf::Vector2<F>& vec) {
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	}

	template <typename F>
	F GetVectorAngle(const sf::Vector2<F>& vec) {
		return Degrees(std::atan2(vec.y, vec.x));
	}

	template <typename F>
	sf::Vector2<F> UnitVector(const F angle) {
		const F theta = Radians(angle);
		return { std::cos(theta), std::sin(theta) };
	}

	template <typename F>
	sf::Vector2<F> GetUnitVector(const sf::Vector2<F>& vec) {
		return (static_cast<F>(1) / GetVectorLength(vec)) * vec;
	}

	template <typename T>
	T GetDotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
		return a.x * b.x + a.y * b.y;
	}

	// NOTE:
	// - since there are only one of two directions a 2D cross product can go,
	//   this function will return a value instead of a vector.
	// - just query the sign of the returned value to get the direction
	template <typename T>
	T GetCrossProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b) {
		return a.x * b.y - a.y * b.x;
	}

}
