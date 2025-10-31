#pragma once

#include <random>

namespace BrightRandom 
{
    static std::mt19937 rng(std::random_device{}());

    int range(int min, int max) 
    {
        std::uniform_int_distribution<> dist(min, max);
        return dist(rng);
    }
}