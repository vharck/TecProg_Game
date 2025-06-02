#include "Utilidade.hpp"

#include <Graphics.hpp>

using namespace std;

using namespace JOGACO;
using namespace Utilidade;

float Utilidade::moveTowards(float current, float target, float maxDelta)
{
    if (abs(target - current) <= maxDelta)
        return target;
    return current + (target > current ? maxDelta : -maxDelta);
}

float Utilidade::distance(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

template <typename T>
const int Utilidade::sign(const T &value)
{
    return value == 0 ? 1 : (T(0) < value) - (value < T(0));
}