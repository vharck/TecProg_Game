#include "Projetil.hpp"

#include "Personagem.hpp"
#include "GerenciadorColisoes.hpp"
#include "Utilidade.hpp"

#include <cmath>

namespace JOGACO
{
    Projetil::Projetil(ProjectileType _projectileType, sf::Vector2f position, sf::Vector2f _direction, float _speed, int _damage, int _lifetime, sf::Vector2f size, Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer layer)
        : Entidade(position, sf::Vector2f(10.f, 10.f), layer),
          type(_projectileType), direction(_direction), speed(_speed), damage(_damage),
          lifetime(_lifetime), currentLifetime(0)
    {
        trigger = new Gerenciadores::GerenciadorColisoes::Trigger(this, position, size, layer);
        trigger->subscribeToCollisionEnter(this, &Projetil::onCollisionEnter);
    }

    Projetil::~Projetil()
    {
    }

    void Projetil::update()
    {
        currentLifetime++;
        if (currentLifetime >= lifetime)
        {
            delete this;
        }

        move();
    }

    void Projetil::onCollisionEnter(Gerenciadores::GerenciadorColisoes::Collider *other)
    {
        try
        {
            Personagem *character = dynamic_cast<Personagem *>(other->getParrentEntity());
            if (character)
            {
                character->getHit(damage);
                delete this;
            }
        }
        catch (const std::bad_cast &e)
        {
            // Se não for um personagem, não faz nada
        }
    }

    void Projetil::move()
    {
        switch (type)
        {
        case ProjectileType::Normal:
            sf::Vector2f newPosition(getPosition() + direction * speed * Utilidade::timeStep);
            setPosition(newPosition);
            break;

        case ProjectileType::Bouncing:
            sf::Vector2f newPosition(direction.x * lifetime * Utilidade::timeStep * speed, std::abs(std::sin(lifetime * Utilidade::timeStep) * speed));
            setPosition(newPosition);
            break;

        case ProjectileType::Explosive:

            break;
        }
    }

    const sf::Vector2f &Projetil::getDirection() const
    {
        return direction;
    }

    void Projetil::setDirection(const sf::Vector2f &newDirection)
    {
        direction = newDirection;
    }
}