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
			TRANSFORMS
	------------------------------------------------------------
	-	MoveVertexArray()
	-	RotateVertexArray()
	-	ScaleVertexArray()
	-	TransformVertexArray()
	-	ShearVertexArray()
	-	ReflectVertexArrayAlongX()
	-	ReflectVertexArrayAlongY()

	------------------------------------------------------------
			SETTERS
	------------------------------------------------------------
	-	SetVertexArrayColor()
	-	SetVertexArrayPosition()

	------------------------------------------------------------
			GETTERS
	------------------------------------------------------------
	-	GetVertexArrayBounds()

	------------------------------------------------------------
			MISC
	------------------------------------------------------------
	-	ResetVertexArray()
	-	SwapVertexArrays()
	-	SwapVerticesInArray()

*/

#include "Mathematics.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <limits>
#include <cstddef>

namespace Arc {

	//////////////////////////////////////////////////////////////////////
	//	TRASNFORMS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	void MoveVertexArray(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& translation) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			vertices[idx].position += translation;
			++idx;
		}
	}

	template <class V>
	void RotateVertexArray(V& vertices, const std::size_t start, const std::size_t count, const float angle, const sf::Vector2f& center = {}) {
		std::size_t idx = start;
		const float theta = Radians(angle);
		const float sin = std::sin(theta);
		const float cos = std::cos(theta);
		for (std::size_t i = 0; i < count; ++i) {
			RotatePoint(vertices[idx].position, sin, cos, center);
			++idx;
		}
	}

	template <class V>
	void ScaleVertexArray(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& scaleFactor, const sf::Vector2f& center = {}) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			ScalePoint(vertices[idx].position, scaleFactor, center);
			++idx;
		}
	}

	template <class V>
	void TransformVertexArray(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& translation, const float angle, const sf::Vector2f& scaleFactor, const sf::Vector2f& center = {}) {
		std::size_t idx = start;
		const float theta = Radians(angle);
		const float sin = std::sin(theta);
		const float cos = std::cos(theta);
		for (std::size_t i = 0; i < count; ++i) {
			TransformPoint(vertices[idx].position, translation, sin, cos, scaleFactor, center);
			++idx;
		}
	}

	template <class V>
	void ShearVertexArray(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& shearFactor, const sf::Vector2f& center = {}) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			ShearPoint(vertices[idx].position, shearFactor, center);
			++idx;
		}
	}

	template <class V>
	void ReflectVertexArrayAlongX(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& center = {}) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			ReflectPointAlongX(vertices[idx].position, center);
			++idx;
		}
	}

	template <class V>
	void ReflectVertexArrayAlongY(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& center = {}) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			ReflectPointAlongY(vertices[idx].position, center);
			++idx;
		}
	}

	//////////////////////////////////////////////////////////////////////
	//	SETTERS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	void SetVertexArrayColor(V& vertices, const std::size_t start, const std::size_t count, const sf::Color& color) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			vertices[idx].color = color;
			++idx;
		}
	}

	template <class V>
	void SetVertexArrayPosition(V& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& position, const sf::Vector2f& center = {}) {
		MoveVertexArray(vertices, start, count, position - center);
	}

	//////////////////////////////////////////////////////////////////////
	//	GETTERS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	sf::FloatRect GetVertexArrayBounds(const V& vertices, const std::size_t start, const std::size_t count) {
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float maxY = std::numeric_limits<float>::min();
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			minX = std::min(minX, vertices[idx].position.x);
			minY = std::min(minX, vertices[idx].position.y);
			maxX = std::max(maxX, vertices[idx].position.x);
			maxY = std::max(maxX, vertices[idx].position.y);
		}
		return { minX, minY, maxX - minX, maxY - minY };
	}

	//////////////////////////////////////////////////////////////////////
	//	MISC
	//////////////////////////////////////////////////////////////////////

	template <class V>
	void ResetVertexArray(V& vertices, const std::size_t start, const std::size_t count, const sf::Vertex& defaultVtx = { {}, sf::Color::Transparent, {} }) {
		std::size_t idx = start;
		for (std::size_t i = 0; i < count; ++i) {
			vertices[idx] = defaultVtx;
			++idx;
		}
	}

	template <class V1, class V2>
	void SwapVertexArrays(V1& vtx1, const std::size_t start1, V2& vtx2, const std::size_t start2, const std::size_t count) {
		std::size_t idx1 = start1;
		std::size_t idx2 = start2;
		for (std::size_t i = 0; i < count; ++i) {
			std::swap(vtx1[idx1], vtx2[idx2]);
			++idx1;
			++idx2;
		}
	}

	template <class V>
	void SwapVertiesInArray(V& vertices, const std::size_t start1, const std::size_t start2, const std::size_t count) {
		SwapVertexArrays(vertices, start1, vertices, start2, count);
	}

}
