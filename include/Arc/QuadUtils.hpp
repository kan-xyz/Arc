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

#include "VertexArrayUtils.hpp"

namespace Arc
{

    template <class VertexArray>
    sf::Vector2f GetQuadCenter(const VertexArray& vertices, const std::size_t id)
    {
        const std::size_t idx = id * 4;
        const sf::Vector2f start = vertices[idx + 0].position;
        const sf::Vector2f end = vertices[idx + 2].position;
        return start + 0.5f * (end - start);
    }

    template <class VertexArray>
    float GetQuadRotation(const VertexArray& vertices, const std::size_t id)
    {
        const std::size_t idx = id * 4;
        const sf::Vector2f dv = vertices[idx + 1].position - vertices[idx + 0].position;
        return Degrees(std::atan2(dv.y, dv.x));
    }

    template <class VertexArray>
    sf::Vector2f GetQuadSize(const VertexArray& vertices, const std::size_t id)
    {
        const std::size_t idx = id * 4;
        const sf::Vector2f dw = vertices[idx + 1].position - vertices[idx + 0].position;
        const sf::Vector2f dh = vertices[idx + 2].position - vertices[idx + 1].position;
        return { std::sqrt(dw.x * dw.x + dw.y * dw.y), std::sqrt(dh.x * dh.x + dh.y * dh.y) };
    }

    template <class VertexArray>
    void MoveQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& translation)
    {
        MoveVertexArray(vertices, id * 4, 4, translation);
    }

    template <class VertexArray>
    void RotateQuad(VertexArray& vertices, const std::size_t id, const float angle)
    {
        RotateVertexArray(vertices, id * 4, 4, angle, GetQuadCenter(vertices, id));
    }

    template <class VertexArray>
    void RotateQuad(VertexArray& vertices, const std::size_t id, const float angle, const sf::Vector2f& center)
    {
        RotateVertexArray(vertices, id * 4, 4, angle, center);
    }

    template <class VertexArray>
    void ScaleQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& scaleFactor)
    {
        ScaleVertexArray(vertices, id * 4, 4, scaleFactor, GetQuadCenter(vertices, id));
    }

    template <class VertexArray>
    void ScaleQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& scaleFactor, const sf::Vector2f& center)
    {
        ScaleVertexArray(vertices, id * 4, 4, scaleFactor, center);
    }

    template <class VertexArray>
    void TransformQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& translation, const float angle, const sf::Vector2f& scaleFactor)
    {
        TransformVertexArray(vertices, id * 4, 4, translation, angle, scaleFactor, GetQuadCenter(vertices, id));
    }

    template <class VertexArray>
    void TransformQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& translation, const float angle, const sf::Vector2f& scaleFactor, const sf::Vector2f& center)
    {
        TransformVertexArray(vertices, id * 4, 4, translation, angle, scaleFactor, center);
    }

    template <class VertexArray>
    void ShearQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& shearFactor)
    {
        ShearVertexArray(vertices, id * 4, 4, shearFactor, GetQuadCenter(vertices, id));
    }

    template <class VertexArray>
    void ShearQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& shearFactor, const sf::Vector2f& center)
    {
        ShearVertexArray(vertices, id * 4, 4, shearFactor, center);
    }

    template <class VertexArray>
    void ReflectQuadAlongX(VertexArray& vertices, const std::size_t id, const sf::Vector2f& center)
    {
        ReflectVertexArrayAlongX(vertices, id * 4, 4, center);
    }

    template <class VertexArray>
    void ReflectQuadAlongY(VertexArray& vertices, const std::size_t id, const sf::Vector2f& center)
    {
        ReflectVertexArrayAlongY(vertices, id * 4, 4, center);
    }

    template <class VertexArray>
    void SetQuadColor(VertexArray& vertices, const std::size_t id, const sf::Color& color)
    {
        SetVertexArrayColor(vertices, id * 4, 4, color);
    }

    template <class VertexArray>
    void SetQuadTextureRect(VertexArray& vertices, const std::size_t id, const sf::FloatRect& textureRect)
    {
        const std::size_t idx = id * 4;
        vertices[idx + 0].texCoords = { textureRect.left, textureRect.top };
        vertices[idx + 1].texCoords = { textureRect.left + textureRect.width, textureRect.top };
        vertices[idx + 2].texCoords = { textureRect.left + textureRect.width, textureRect.top + textureRect.height };
        vertices[idx + 3].texCoords = { textureRect.left, textureRect.top + textureRect.height };
    }

    template <class VertexArray>
    void MakeRect(VertexArray& vertices, const std::size_t id, const sf::FloatRect& rect)
    {
        const std::size_t idx = id * 4;
        vertices[idx + 0].position = { rect.left, rect.top };
        vertices[idx + 1].position = { rect.left + rect.width, rect.top };
        vertices[idx + 2].position = { rect.left + rect.width, rect.top + rect.height };
        vertices[idx + 3].position = { rect.left, rect.top + rect.height };
    }

    template <class VertexArray>
    void MakeQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& position, const sf::Vector2f& size)
    {
        const std::size_t idx = id * 4;
        vertices[idx + 0].position = position + 0.5f * sf::Vector2f(-size.x, -size.y);
        vertices[idx + 1].position = position + 0.5f * sf::Vector2f(size.x, -size.y);
        vertices[idx + 2].position = position + 0.5f * sf::Vector2f(size.x, size.y);
        vertices[idx + 3].position = position + 0.5f * sf::Vector2f(-size.x, size.y);
    }

    template <class VertexArray>
    void MakeQuad(VertexArray& vertices, const std::size_t id, const sf::Vector2f& position, const sf::Vector2f& size, const float angle, const sf::Color& color, const sf::FloatRect& textureRect)
    {
        MakeQuad(vertices, id, position, size);
        RotateQuad(vertices, id, angle);
        SetQuadColor(vertices, id, color);
        SetQuadTextureRect(vertices, id, textureRect);
    }

    template <class VertexArray>
    void MakeGrid(VertexArray& vertices, const std::size_t start, const sf::Vector2u& gridsize, const sf::Vector2f& cellSize, const sf::Vector2f& position = sf::Vector2f(), const sf::Vector2f& padding = sf::Vector2f())
    {
        std::size_t idx = start;
        float Y = position.y;
        for (unsigned int y = 0; y < gridsize.y; ++y)
        {
            float X = position.x;
            for (unsigned int x = 0; x < gridsize.x; ++x)
            {
                MakeRect(vertices, idx, { sf::Vector2f(X, Y), cellSize });
                ++idx;
                X += cellSize.x + padding.x;
            }
            Y += cellSize.y + padding.y;
        }
    }

    template <class VertexArray>
    void MakeDiamond(VertexArray& vertices, const std::size_t id, const sf::Vector2f& position, const float width, const float height)
    {
        const std::size_t idx = id * 4;
        vertices[idx + 0].position = position + 0.5f * sf::Vector2f(0.0f, -height);
        vertices[idx + 1].position = position + 0.5f * sf::Vector2f(width, 0.0f);
        vertices[idx + 2].position = position + 0.5f * sf::Vector2f(0.0f, height);
        vertices[idx + 3].position = position + 0.5f * sf::Vector2f(-width, 0.0f);
    }

    template <class VertexArray>
    void SetQuadPosition(VertexArray& vertices, const std::size_t id, const sf::Vector2f& position)
    {
        SetVertexArrayPosition(vertices, id * 4, 4, position, GetQuadCenter(vertices, id));
    }

    template <class VertexArray>
    void SetQuadSize(VertexArray& vertices, const std::size_t id, const sf::Vector2f& size)
    {
        MakeQuad(vertices, id, GetQuadCenter(vertices, id), size);
    }

    template <class VertexArray>
    void SetQuadRotation(VertexArray& vertices, const std::size_t id, const float angle)
    {
        RotateQuad(vertices, id, angle - GetQuadRotation(vertices, id));
    }

    template <class VertexArray>
    sf::FloatRect GetQuadBounds(const VertexArray& vertices, const std::size_t id)
    {
        return GetVertexArrayBounds(vertices, id * 4, 4);
    }

}
