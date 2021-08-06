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

#include "PointUtils.hpp"
#include "Mathematics.hpp"
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cmath>

namespace Arc
{

    template <class VertexArray>
    void MoveVertexArray(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& translation)
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            vertices[i].position += translation;
        }
    }

    template <class VertexArray>
    void RotateVertexArray(VertexArray& vertices, const std::size_t start, const std::size_t count, const float angle, const sf::Vector2f& center = sf::Vector2f())
    {
        const float theta = Radians(angle);
        const float sin = std::sin(theta);
        const float cos = std::cos(theta);
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            RotatePoint(vertices[i].position, sin, cos, center);
        }
    }

    template <class VertexArray>
    void ScaleVertexArray(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& scaleFactor, const sf::Vector2f& center = sf::Vector2f())
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            ScalePoint(vertices[i].position, scaleFactor, center);
        }
    }

    template <class VertexArray>
    void TransformVertexArray(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& translation, const float angle, const sf::Vector2f& scaleFactor, const sf::Vector2f& center = sf::Vector2f())
    {
        const float theta = Radians(angle);
        const float sin = std::sin(theta);
        const float cos = std::cos(theta);
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            TransformPoint(vertices[i].position, translation, sin, cos, scaleFactor, center);
        }
    }

    template <class VertexArray>
    void ShearVertexArray(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& shearFactor, const sf::Vector2f& center = sf::Vector2f())
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            ShearPoint(vertices[i].position, shearFactor, center);
        }
    }

    template <class VertexArray>
    void ReflectVertexArrayAlongX(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& center = sf::Vector2f())
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            ReflectPointAlongX(vertices[i].position, center);
        }
    }

    template <class VertexArray>
    void ReflectVertexArrayAlongY(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& center = sf::Vector2f())
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            ReflectPointAlongY(vertices[i].position, center);
        }
    }

    template <class VertexArray>
    void SetVertexArrayPosition(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Vector2f& position, const sf::Vector2f& center = sf::Vector2f())
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            vertices[i].position += position - center;
        }
    }

    template <class VertexArray>
    void SetVertexArrayColor(VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::Color& color)
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            vertices[i].color = color;
        }
    }

    template <class VertexArray>
    sf::FloatRect GetVertexArrayBounds(const VertexArray& vertices, const std::size_t start, const std::size_t count)
    {
        const std::size_t end = start + count;
        float minX = std::numeric_limits<float>::max();
        float minY = std::numeric_limits<float>::max();
        float maxX = std::numeric_limits<float>::min();
        float maxY = std::numeric_limits<float>::min();
        for (std::size_t i = start; i < end; ++i)
        {
            minX = std::min(minX, vertices[i].position.x);
            minY = std::min(minY, vertices[i].position.y);
            maxX = std::max(maxX, vertices[i].position.x);
            maxY = std::max(maxY, vertices[i].position.y);
        }
        return { minX, minY, maxX - minX, maxY - minY };
    }

    template <class VertexArray>
    bool VertexArrayInRect(const VertexArray& vertices, const std::size_t start, const std::size_t count, const sf::FloatRect& rect)
    {
        const std::size_t end = start + count;
        for (std::size_t i = start; i < end; ++i)
        {
            if (!rect.contains(vertices[i].position))
            {
                return false;
            }
        }
        return true;
    }

}
