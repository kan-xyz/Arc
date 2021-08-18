#pragma once

//  Arc - SFML Vertex Array Utilities
//  Copyright (C) 2021 Kan
//    
//  This software is provided 'as-is', without any express or implied warranty.
//  In no event will the authors be held liable for any damages arising from the use of this software.
//
//  Permission is granted to anyone to use this software for any purpose, including commercial applications,
//  and to alter it and redistribute it freely, subject to the following restrictions:
//
//      1. The origin of this software must not be misrepresented;
//         you must not claim that you wrote the original software.
//         If you use this software in a product, an acknowledgment
//         in the product documentation would be appreciated but
//         is not required.
//
//      2. Altered source versions must be plainly marked as such,
//         and must not be misrepresented as being the original software.
//
//      3. This notice may not be removed or altered from any source distribution.

#include "QuadUtils.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

namespace Arc
{

    // NOTE:
    // SFML vertex arrays can only work on one texture per vertex array.
    // this class is meant to get around those limitations and place multiple
    // textures under one vertex array
    template <typename Type>
    class BasicTextureAtlas
    {
    public:

        BasicTextureAtlas() = default;

        bool Create(const sf::Vector2u& gridSize, const sf::Vector2u& cellSize)
        {
            m_GridSize = gridSize;
            m_CellSize = cellSize;
            const unsigned int size = gridSize.x * gridSize.y;
            m_TextureRects.resize(static_cast<std::size_t>(size));
            m_TextureRects.shrink_to_fit();
            std::size_t idx = 0;

            for (unsigned int y = 0; y < m_GridSize.y; ++y)
            {
                const unsigned int Y = y * m_CellSize.y;
                for (unsigned int x = 0; x < m_GridSize.x; ++x)
                {
                    const unsigned int X = x * m_CellSize.x;
                    m_TextureRects[idx] = { static_cast<Type>(X), static_cast<Type>(Y), static_cast<Type>(m_CellSize.x), static_cast<Type>(m_CellSize.y) };
                    ++idx;
                }
            }

            if (!m_RenderTexture.create(m_GridSize.x * m_CellSize.x, m_GridSize.y * m_CellSize.y)) { return false; }
            Clear();
            return true;
        }

        bool EditCell(const std::size_t index, const sf::Texture& texture, const sf::Rect<Type>& rect)
        {
            if (index >= m_TextureRects.size()) { return false; }
            sf::Vertex vertices[4];
            MakeRect(vertices, 0, sf::FloatRect(m_TextureRects[index]));
            m_RenderTexture.draw(&vertices[0], 4, sf::Quads, &texture);
            return true;
        }

        const sf::Rect<Type>& GetRect(const std::size_t index) const { return m_TextureRects[index]; }
        void Display() { m_RenderTexture.display(); }
        void Clear() { m_RenderTexture.clear({ 0, 0, 0, 0 }); }
        const sf::Texture& GetTexture() const { return m_RenderTexture.getTexture(); }
        const sf::Vector2u& GetGridSize() const { return m_GridSize; }
        const sf::Vector2u& GetCellSize() const { return m_CellSize; }
        
        bool SaveToFile(const std::string& filename)
        {
            sf::Image image = m_RenderTexture.getTexture().copyToImage();
            return image.saveToFile(filename);
        }

    private:
        sf::RenderTexture m_RenderTexture;
        std::vector<sf::Rect<Type>> m_TextureRects;
        sf::Vector2u m_GridSize, m_CellSize;
    };

    using TextureAtlas = BasicTextureAtlas<int>;

}
