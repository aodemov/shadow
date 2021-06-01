#pragma once

#include <random>

namespace Shadow {

class Random {
public:
    static void Init() {
        sRandomEngine.seed(std::random_device()());
    }

    static float Float() {
        return (float)sDistribution(sRandomEngine) / (float)std::numeric_limits<std::mt19937::result_type>::max();
    }

    static float Float(float from, float to) {
        return Float() * (to - from) + from;
    }

    static uint32_t Int(int from, int to) {
        return (int)Float((float)from, (float)to);
    }

private:
    static std::mt19937 sRandomEngine;
    static std::uniform_int_distribution<std::mt19937::result_type> sDistribution;
};

}