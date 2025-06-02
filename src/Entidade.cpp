// Game Object

#include "Entidade.hpp"

#include "GerenciadorColisoes.hpp"

using namespace sf;
using namespace std;

namespace JOGACO
{
    Entidade::Entidade()
        : Ente(), position(0.0f, 0.0f), size(0.0f, 0.0f), buffer(cout.rdbuf())
    {
        collider = new Gerenciadores::GerenciadorColisoes::Physic(position, Vector2f(0.0f, 0.0f), Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer::Ground);
    }

    Entidade::Entidade(Vector2f position, Vector2f size, Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer layer)
        : Ente(), position(position), size(size), buffer(cout.rdbuf())
    {
        collider = new Gerenciadores::GerenciadorColisoes::Physic(position, size, layer);
    }

    Entidade::~Entidade()
    {
        delete collider;
        collider = nullptr;
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