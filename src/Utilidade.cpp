#include "Utilidade.hpp"

using namespace std;

using namespace JOGACO;
using namespace Utilidade;

float Utilidade::moveTowards(float current, float target, float maxDelta)
{
    if (std::abs(target - current) <= maxDelta)
        return target;
    return current + (target > current ? maxDelta : -maxDelta);
}

template <typename T>
const int Utilidade::sign(const T &value)
{
    return value == 0 ? 1 : (T(0) < value) - (value < T(0));
}