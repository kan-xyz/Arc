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

#include <random>

namespace Arc
{

    template <typename GenType>
    class RNG
    {
    public:

        RNG()
        {
            Init();
        }

        void Init()
        {
            Seed(std::random_device{}());
        }

        void Seed(const unsigned int seed)
        {
            m_RNG.seed(seed);
        }

        template <typename Type>
        Type Range(const Type minVal, const Type maxVal)
        {
            if constexpr (std::is_integral_v<Type>)
            {
                std::uniform_int_distribution<Type> dist(minVal, maxVal);
                return dist(m_RNG);
            }
            else if constexpr (std::is_floating_point_v<Type>)
            {
                std::uniform_real_distribution<Type> dist(minVal, maxVal);
                return dist(m_RNG);
            }
            else if constexpr (std::is_same_v<Type, std::uint8_t> || std::is_same_v<Type, std::int8_t>)
            {
                std::uniform_int_distribution<int> dist(minVal, maxVal);
                return static_cast<Type>(dist(m_RNG));
            }
        }

        template <typename Type>
        Type Offset(const Type center, const Type offset)
        {
            return Range(center - offset, center + offset);
        }

        template <typename Type>
        Type Gaussian(const Type mean, const Type stddev)
        {
            std::normal_distribution dist(mean, stddev);
            return dist(m_RNG);
        }

        bool Bernoulli(const bool successProbability)
        {
            std::bernoulli_distribution dist(successProbability);
            return dist(m_RNG);
        }

        GenType& GetGenerator()
        {
            return m_RNG;
        }

    private:
        GenType m_RNG;
    };

}
