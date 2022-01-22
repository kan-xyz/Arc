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
	-	MoveQuad()
	-	RotateQuad()
	-	ScaleQuad()
	-	TransformQuad()
	-	ShearQuad()

	------------------------------------------------------------
			GETTERS
	------------------------------------------------------------
	-	GetQuadCenter()
	-	GetQuadAngle()
	-	GetQuadSize()
	-	GetQuadBounds()

	------------------------------------------------------------
			SETTERS
	------------------------------------------------------------
	-	SetQuadColor()
	-	SetQuadPosition()
	-	SetQuadSize()
	-	SetQuadRotation()

	------------------------------------------------------------
			MAKERS
	------------------------------------------------------------
	-	MakeQuad()
	-	MakeGrid()
	-	MakeRect()
	-	MakeQuadLine()

*/

#include "VertexArrayUtils.hpp"

namespace Arc {

	//////////////////////////////////////////////////////////////////////
	//	GETTERS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	sf::Vector2f GetQuadCenter(const V& vertices, const std::size_t id) {
		const std::size_t idx = id * 4;
		return Lerp(vertices[idx + 0].position, vertices[idx + 2].position, 0.5f);
	}

	template <class V>
	sf::Vector2f GetQuadSize(const V& vertices, const std::size_t id) {
		const std::size_t idx = id * 4;
		return { GetVectorLength(vertices[idx + 1].position - vertices[idx + 0].position), GetVectorLength(vertices[idx + 2].position - vertices[idx + 1].position) };
	}

	template <class V>
	float GetQuadRotation(const V& vertices, const std::size_t id) {
		const std::size_t idx = id * 4;
		return GetVectorAngle(vertices[idx + 1].position - vertices[idx + 0].position);
	}

	template <class V>
	sf::FloatRect GetQuadBounds(const V& vertices, const std::size_t id) {
		return GetVertexArrayBounds(vertices, id * 4, 4);
	}

	//////////////////////////////////////////////////////////////////////
	//	TRANSFORMS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	void MoveQuad(V& vertices, const std::size_t id, const sf::Vector2f& translation) {
		MoveVertexArray(vertices, id * 4, 4, translation);
	}

	template <class V>
	void RotateQuad(V& vertices, const std::size_t id, const float angle, const sf::Vector2f& center) {
		RotateVertexArray(vertices, id * 4, 4, angle, center);
	}

	template <class V>
	void RotateQuad(V& vertices, const std::size_t id, const float angle) {
		RotateQuad(vertices, id, angle, GetQuadCenter(vertices, id));
	}

	template <class V>
	void ScaleQuad(V& vertices, const std::size_t id, const sf::Vector2f& scaleFactor, const sf::Vector2f& center) {
		ScaleVertexArray(vertices, id * 4, 4, scaleFactor, center);
	}

	template <class V>
	void ScaleQuad(V& vertices, const std::size_t id, const sf::Vector2f& scaleFactor) {
		ScaleQuad(vertices, id, scaleFactor, GetQuadCenter(vertices, id));
	}

	template <class V>
	void TransformQuad(V& vertices, const std::size_t id, const sf::Vector2f& translation, const float angle, const sf::Vector2f& scaleFactor, const sf::Vector2f& center) {
		TransformVertexArray(vertices, id * 4, 4, translation, angle, scaleFactor, center);
	}

	template <class V>
	void TransformQuad(V& vertices, const std::size_t id, const sf::Vector2f& translation, const float angle, const sf::Vector2f& scaleFactor) {
		TransformVertexArray(vertices, id * 4, 4, translation, angle, scaleFactor, GetQuadCenter(vertices, id));
	}

	template <class V>
	void ShearQuad(V& vertices, const std::size_t id, const sf::Vector2f& shearFactor, const sf::Vector2f& center = {}) {
		ShearVertexArray(vertices, id * 4, 4, shearFactor, center);
	}

	template <class V>
	void ShearQuad(V& vertices, const std::size_t id, const sf::Vector2f& shearFactor) {
		ShearVertexArray(vertices, id * 4, 4, shearFactor, GetQuadCenter(vertices, id));
	}

	//////////////////////////////////////////////////////////////////////
	//	SETTERS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	void SetQuadPosition(V& vertices, const std::size_t id, const sf::Vector2f& position) {
		SetVertexArrayPosition(vertices, id * 4, 4, position, GetQuadCenter(vertices, id));
	}

	template <class V>
	void SetQuadColor(V& vertices, const std::size_t id, const sf::Color& color) {
		SetVertexArrayColor(vertices, id * 4, 4, color);
	}

	template <class V>
	void SetQuadTextureRect(V& vertices, const std::size_t id, const sf::FloatRect& textureRect) {
		const std::size_t idx = id * 4;
		vertices[idx + 0].texCoords = { textureRect.left, textureRect.top };
		vertices[idx + 1].texCoords = { textureRect.left + textureRect.width, textureRect.top };
		vertices[idx + 2].texCoords = { textureRect.left + textureRect.width, textureRect.top + textureRect.height };
		vertices[idx + 3].texCoords = { textureRect.left, textureRect.top + textureRect.height };
	}

	//////////////////////////////////////////////////////////////////////
	//	MAKERS
	//////////////////////////////////////////////////////////////////////

	template <class V>
	void MakeRect(V& vertices, const std::size_t id, const sf::FloatRect& rect) {
		const std::size_t idx = id * 4;
		vertices[idx + 0].position = { rect.left, rect.top };
		vertices[idx + 1].position = { rect.left + rect.width, rect.top };
		vertices[idx + 2].position = { rect.left + rect.width, rect.top + rect.height};
		vertices[idx + 3].position = { rect.left, rect.top + rect.height};
	}
	
	template <class V>
	void MakeQuad(V& vertices, const std::size_t id, const sf::Vector2f& center, const sf::Vector2f& size) {
		const std::size_t idx = id * 4;
		vertices[idx + 0].position = { -0.5f * size.x + center.x, -0.5f * size.y + center.y };
		vertices[idx + 1].position = {  0.5f * size.x + center.x, -0.5f * size.y + center.y };
		vertices[idx + 2].position = {  0.5f * size.x + center.x,  0.5f * size.y + center.y };
		vertices[idx + 3].position = { -0.5f * size.x + center.x,  0.5f * size.y + center.y };
	}

	template <class V>
	void MakeDiamond(V& vertices, const std::size_t id, const float width, const float height, const sf::Vector2f& center) {
		const std::size_t idx = id * 4;
		vertices[idx + 0].position = { 0.0f, -0.5f * height };
		vertices[idx + 1].position = { 0.5f * width, 0.0f };
		vertices[idx + 2].position = { 0.0f, 0.5f * height };
		vertices[idx + 3].position = { -0.5f * width, 0.0f };
	}

	template <class V>
	void MakeGrid(V& vertices, const std::size_t start, const sf::Vector2u& gridSize, const sf::Vector2f& cellSize, const sf::Vector2f& position = {}, const sf::Vector2f& padding = {}) {
		std::size_t idx = start;
		float yPos = position.y;
		for (unsigned int y = 0; y < gridSize.y; ++y) {
			float xPos = position.x;
			for (unsigned int x = 0; x < gridSize.x; ++x) {
				MakeRect(vertices, idx, { xPos, yPos, cellSize.x, cellSize.y });
				++idx;
				xPos += cellSize.x + padding.x;
			}
			yPos += cellSize.y + padding.y;
		}
	}

	template <class V>
	void MakeQuadLine(V& vertices, const std::size_t id, const sf::Vector2f& start, const sf::Vector2f& end, const float thickness = 1.0f) {
		MakeRect(vertices, id, { 0.0f, 0.5f * thickness, GetVectorLength(end - start), thickness });
		RotateQuad(vertices, id, GetVectorAngle(end - start), { 0.0f, 0.0f });
		MoveQuad(vertices, id, start);
	}

}
