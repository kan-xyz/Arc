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

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace Arc
{

    //-----------------------------------------------------------------------------------------------------------------
    // TRIGONOMETRY HELPERS
    //-----------------------------------------------------------------------------------------------------------------

    template <typename Type>
    constexpr Type Pi()
    {
        static_assert(std::is_floating_point_v<Type>, "Arc mathematical functions need to be in floating point types");
        return static_cast<Type>(3.14159265358979323846);
    }

    template <typename Type>
    Type Radians(const Type degrees)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc mathematical functions need to be in floating point types");
        return (Pi<Type>() / static_cast<Type>(180)) * degrees;
    }

    template <typename Type>
    Type Degrees(const Type radians)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc mathematical functions need to be in floating point types");
        return (static_cast<Type>(180) / Pi<Type>()) * radians;
    }

    //-----------------------------------------------------------------------------------------------------------------
    // POINT TRANSFORMS
    //-----------------------------------------------------------------------------------------------------------------

    template <typename Type>
    void RotatePoint(sf::Vector2<Type>& point, const Type sin, const Type cos, const sf::Vector2<Type>& center = sf::Vector2<Type>())    
    {
        point = { (point.x - center.x) * cos - (point.y - center.y) * sin + center.x, (point.x - center.x) * sin + (point.y - center.y) * cos + center.y };
    }

    template <typename Type>
    void ScalePoint(sf::Vector2<Type>& point, const sf::Vector2<Type>& scaleFactor, const sf::Vector2<Type>& center = sf::Vector2<Type>())
    {
        point = { (point.x - center.x) * scaleFactor.x + center.x, (point.y - center.y) * scaleFactor.y + center.y };
    }

    template <typename Type>
    void TransformPoint(sf::Vector2<Type>& point, const sf::Vector2<Type>& translation, const Type sin, const Type cos, const sf::Vector2<Type>& scaleFactor, const sf::Vector2<Type>& center = sf::Vector2<Type>())
    {
        point = { scaleFactor.x * ((point.x - center.x) * cos - (point.y - center.y) * sin) + translation.x + center.x, scaleFactor.y * ((point.x - center.x) * sin + (point.y - center.y) * cos) + translation.y + center.y };
    }

    template <typename Type>
    void ShearPoint(sf::Vector2<Type>& point, const sf::Vector2<Type>& shearFactor, const sf::Vector2<Type>& center = sf::Vector2<Type>())
    {
        point = { (static_cast<Type>(1) + shearFactor.x * shearFactor.y) * (point.x - center.x) + shearFactor.y * (point.y - center.y) + center.x, shearFactor.x * (point.x - center.x) + point.y };
    }

    template <typename Type>
    void ReflectPointAlongX(sf::Vector2<Type>& point, const sf::Vector2<Type>& center = sf::Vector2<Type>())
    {
        point.y = -point.y + static_cast<Type>(2) * center.y;
    }

    template <typename Type>
    void ReflectPointAlongY(sf::Vector2<Type>& point, const sf::Vector2<Type>& center = sf::Vector2<Type>())
    {
        point.x = -point.x + static_cast<Type>(2) * center.x;
    }

}
