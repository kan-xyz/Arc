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

#include <type_traits>

namespace Arc
{

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

}
