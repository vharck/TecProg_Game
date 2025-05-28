// Game Object

#include "Entidade.hpp"

using namespace sf;
using namespace std;

namespace JOGACO
{
    Entidade::Entidade()
        : Ente(), position(0.0f, 0.0f), buffer(cout.rdbuf())
    {
    }

    Entidade::Entidade(Vector2f position)
        : Ente(), position(position), buffer(cout.rdbuf())
    {
    }

    Entidade::~Entidade()
    {
    }

    void Entidade::saveDataBuffer()
    {
        // ??
    }

    Vector2f Entidade::getPosition() const
    {
        return position;
    }

    const float Entidade::getGravity() const
    {
        return gravity;
    }

    void Entidade::setPosition(const Vector2f &newPosition)
    {
        position = newPosition;
    }
}