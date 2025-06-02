#pragma once
#include <cmath>

namespace JOGACO
{
    namespace Utilidade
    {
        const float timeStep = 0.016f; // 60 FPS -> 0.016

        float moveTowards(float current, float target, float maxDelta);

        template <typename T>
        const int sign(const T &value);

        float distance(const sf::Vector2f &a, const sf::Vector2f &b);
    }
}