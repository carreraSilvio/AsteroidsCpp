#pragma once

#include <random>

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
}