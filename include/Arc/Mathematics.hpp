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
        static_assert(std::is_floating_point_v<Type>, "Arc::Pi needs to be in floating point types");
        return static_cast<Type>(3.14159265358979323846264338327950288);
    }

    template <typename Type>
    Type Radians(const Type degrees)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc::Radians functions need to be in floating point types");
        return (Pi<Type>() / static_cast<Type>(180)) * degrees;
    }

    template <typename Type>
    Type Degrees(const Type radians)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc::Degrees functions need to be in floating point types");
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

    //-----------------------------------------------------------------------------------------------------------------
    // INTERPOLATION
    //-----------------------------------------------------------------------------------------------------------------

    template <typename Type, typename FloatType>
    Type Lerp(const Type start, const Type end, const FloatType t)
    {
        static_assert(std::is_floating_point_v<FloatType>, "Arc::Lerp third parameter must take in a floating point type");
        const FloatType s = static_cast<FloatType>(start);
        const FloatType e = static_cast<FloatType>(end);
        const FloatType result = s * (static_cast<FloatType>(1) - t) + t * e;
        return static_cast<Type>(result);
    }

    template <typename Type, typename FloatType>
    Type CosineLerp(const Type start, const Type end, const FloatType t)
    {
        static_assert(std::is_floating_point_v<FloatType>, "Arc::CosineLerp third parameter must take in a floating point type");
        const FloatType T = static_cast<FloatType>(1) - (static_cast<FloatType>(0.5) * std::cos(t * Pi<FloatType>()));
        return Lerp(start, end, T);
    }

    //-----------------------------------------------------------------------------------------------------------------
    // VECTOR OPERATIONS
    //-----------------------------------------------------------------------------------------------------------------

    template <typename Type>
    Type GetVectorLength(const sf::Vector2<Type>& vec)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc::GetVectorLength must have a floating point type to work");
        return std::sqrt(vec.x * vec.x + vec.y * vec.y);
    }

    template <typename Type>
    Type GetVectorAngle(const sf::Vector2<Type>& vec)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc::GetVectorAngle must have a floating point type to work");
        return Degrees(std::atan2(vec.y, vec.x));
    }

    template <typename Type>
    sf::Vector2<Type> UnitVector(const Type angle)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc::UnitVector must have a floating point type for the angle");
        const Type theta = Radians(angle);
        return { std::cos(theta), std::sin(angle) };
    }

    template <typename Type>
    sf::Vector2<Type> GetUnitVector(const sf::Vector2<Type>& vec)
    {
        static_assert(std::is_floating_point_v<Type>, "Arc::GetUnitVector must take in a vector with floating point type coordinates");
        const Type length = GetVectorLength(vec);
        return (static_cast<Type>(1) . length) * vec;
    }

    template <typename Type>
    Type GetDotProduct(const sf::Vector2<Type>& a, const sf::Vector2<Type>& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    // NOTE: 
    // since there is only one of two directions the 2D cross product can go, this function will return a value instead of a vector.
    // just query the sign of the return value in order to get the direction
    template <typename Type>
    Type GetCrossProduct(const sf::Vector2<Type>& a, const sf::Vector2<Type>& b)
    {
        return a.x * b.y - a.y * b.x;
    }

}
