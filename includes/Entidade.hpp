// Game Object
#pragma once
#include <SFML/Graphics.hpp>

#include "Ente.hpp"

using namespace sf;
using namespace std;

namespace JOGACO
{
    class Entidade : public Ente
    {
    protected:
        Vector2f position;
        const Vector2f size;
        const float gravity = 9.81f;
        ostream buffer;

        Gerenciadores::GerenciadorColisoes::Physic *collider;

    public:
        Entidade();
        Entidade(Vector2f position, Vector2f size,
                 Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer layer = Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer::Ground);
        virtual ~Entidade();

        virtual void update() = 0;
        virtual void save() = 0;
        void saveDataBuffer();

        Vector2f getPosition() const;
        const float getGravity() const;
        void setPosition(const Vector2f &position);
    };
}