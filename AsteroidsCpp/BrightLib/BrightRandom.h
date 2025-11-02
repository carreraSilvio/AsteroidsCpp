#pragma once

#include <random>
#include <SFML/System.hpp>

namespace BrightRandom 
{
    static std::mt19937 rng(std::random_device{}());

    inline int range(int min, int max)
    {
        std::uniform_int_distribution<> dist(min, max);
        return dist(rng);
    }

    inline float range(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    template<typename T>
    inline T range(const std::vector<T>& values)
    {
        std::uniform_int_distribution<size_t> dist(0, values.size() - 1);
        return values[dist(rng)];
    }

    /// <summary>
    ///  Generates a random float between min and max using a fixed step size.
    ///   Each possible value in the sequence (min, min + step, ..., max) 
    /// </summary>
    inline float range(float min, float max, float step)
    {
        int steps = static_cast<int>((max - min) / step);
        std::uniform_int_distribution<int> dist(0, steps);
        return min + dist(rng) * step;
    }

    inline sf::Vector2f getRandomNormalizedDirection()
    {
        float angle = range(0.0f, 2.0f * 3.14f);
        return sf::Vector2f(std::cos(angle), std::sin(angle));
    }
}