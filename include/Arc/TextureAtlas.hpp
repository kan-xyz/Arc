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
			CLASS MEMBER FUNCTIONS
	------------------------------------------------------------
	-	Create()
	-	EditCell()
	-	Clear()
	-	Display()
	-	GetTexture()
	-	GetGridSize()
	-	GetCellSize()
	-	GetRect();
	-	SaveToImage()

	------------------------------------------------------------
			BASIC USAGE
	------------------------------------------------------------

	int main() {

		// decalre the texture atlas
		Arc::BasicTextureAtlas<int> texture_rects;
		texture_rects.Create({ 1, 3 }, { 32, 32 }); // this creates a 1x3 grid of texture tiles of size 32x32 pixels

		sf::Texture texture1;
		sf::Texture texture2;
		sf::Texture texture3;

		texture1.loadFromFile("file1");
		texture2.loadFromFile("file2");
		texture3.loadFromFile("file3");

		// insert the textures
		texture_rects.EditCell(0, texture1); // this adds the whole texture
		texture_rects.EditCell(1, texture2, { 32, 32, 32, 32 }); // this adds a portion of the texture defined by left, top, width and height of the rectangle
		texture_rects.EditCell(2, texture3, { 32, 128, 16, 32 }); // this adds a portion of the texture defined by left, top, width and height of the rectangle
		texture_rects.Display(); // call this once you're done with editing the texture atlas

		sf::Sprite sprite1;
		sf::Sprite sprite2;
		sf::Sprite sprite3;

		// use the textures
		sprite1.setTexture(textre_rects.GetTexture());
		sprite2.setTexture(textre_rects.GetTexture());
		sprite3.setTexture(textre_rects.GetTexture());

		sprite1.setTextureRect(textre_rects.GetRect(0));
		sprite2.setTextureRect(textre_rects.GetRect(1));
		sprite3.setTextureRect(textre_rects.GetRect(2));

	}

*/

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <vector>

namespace Arc {

	// NOTE:
	// - since SFML vertex arrays can only work on one texture per vertex array
	//   this class or something like it will be needed for placing multiple textures
	//   under one vertex array
	template <typename T>
	class BasicTextureAtlas {
	public:

		BasicTextureAtlas() = default;

		bool Create(const sf::Vector2u& gridSize, const sf::Vector2u& cellSize) {
			m_gridSize = gridSize;
			m_cellSize = cellSize;
			const unsigned int size = m_gridSize.x * m_gridSize.y;
			m_rects.resize(static_cast<std::size_t>(size));
			m_rects.shrink_to_fit();
			std::size_t idx = 0;
			for (unsigned int y = 0; y < m_gridSize.y; ++y) {
				const T Y = static_cast<T>(y) * static_cast<T>(cellSize.y);
				for (unsigned int x = 0; x < m_gridSize.x; ++x) {
					const T X = static_cast<T>(x) * static_cast<T>(m_cellSize.y);
					m_rects[idx] = { X, Y, static_cast<T>(m_cellSize.x), static_cast<T>(m_cellSize.y) };
					++idx;
				}
			}
			if (!m_texture.create(m_gridSize.x, m_gridSize.y)) { return false; }
			Clear();
			return true;
		}

		bool EditCell(const std::size_t index, const sf::Texture& texture, const sf::IntRect& rect = sf::IntRect()) {
			if (index >= m_rects.size()) { return false; }
			sf::RectangleShape r;
			r.setPosition(sf::Vector2f(sf::Vector2<T>(m_rects[index].left, m_rects[index].top)));
			r.setSize(sf::Vector2f(sf::Vector2<T>(m_rects[index].width, m_rects[index].height)));
			r.setTexture(&texture);
			r.setTextureRect(rect);
			m_texture.draw(r);
			return true;
		}

		bool EditCell(const sf::Vector2u& position, const sf::Texture& texture, const sf::IntRect& rect = sf::IntRect()) {
			const unsigned int x = position.x * m_cellSize.x;
			const unsigned int y = position.y * m_cellSize.y;
			if (!(x <= m_gridSize.x) || !(y <= m_gridSize.y)) { return false; }
			sf::RectangleShape r;
			r.setPosition(sf::Vector2f(sf::Vector2u(x, y)));
			r.setSize(sf::Vector2f(m_cellSize));
			r.setTexture(&texture);
			r.setTextureRect(rect);
			m_texture.draw(r);
		}

		bool EditCell(const sf::Vector2u& position, const sf::Vector2u& size, const sf::Texture& texture, const sf::IntRect& rect = sf::IntRect()) {
			const unsigned int x = position.x * m_cellSize.x;
			const unsigned int y = position.y * m_cellSize.y;
			const unsigned int w = size.x * m_cellSize.x;
			const unsigned int h = size.y * m_cellSize.y;
			if (!(x <= m_gridSize.x) || !(y <= m_gridSize.y)) { return false; }
			sf::RectangleShape r;
			r.setPosition(sf::Vector2f(sf::Vector2u(x, y)));
			r.setSize(sf::Vector2f(sf::Vector2u(w, h)));
			r.setTexture(&texture);
			r.setTextureRect(rect);
			m_texture.draw(r);
		}

		void Clear() { m_texture.clear(sf::Color::Transparent); }
		void Display() { m_texture.display(); }
		const sf::Texture& GetTexture() const { return m_texture.getTexture(); }
		const sf::Vector2u& GetGridSize() const { return m_gridSize; }
		const sf::Rect<T>& GetGetRect(const std::size_t index) { return m_rects[index]; };

		const sf::Rect<T>& GetGetRect(const sf::Vector2u& gridPosition) {
			const unsigned int x = m_cellSize.x * gridPosition.x;
			const unsigned int y = m_cellSize.y * gridPosition.y;
			const sf::Vector2<T> siz = sf::Vector2<T>(m_cellSize);
			return { static_cast<T>(x), static_cast<T>(y), siz.x, siz.y };
		}
		
		const sf::Rect<T>& GetGetRect(const sf::Vector2u& gridPosition, const sf::Vector2u& size) {
			const unsigned int x = m_cellSize.x * gridPosition.x;
			const unsigned int y = m_cellSize.y * gridPosition.y;
			const unsigned int w = m_cellSize.y * size.y;
			const unsigned int h = m_cellSize.y * size.y;
			return { static_cast<T>(x), static_cast<T>(y), static_cast<T>(w), static_cast<T>(h) };
		}

		bool SaveToFile(const std::string& file) {
			sf::Image img = m_texture.getTexture().copyToImage();
			return img.saveToFile(file);
		}

	private:
		sf::RenderTexture m_texture;
		std::vector<sf::Rect<T>> m_rects;
		sf::Vector2u m_gridSize;
		sf::Vector2u m_cellSize;
	};

	using TextureAtlas = BasicTextureAtlas<int>;

}
