// Character

#include "Personagem.hpp"

using namespace sf;
using namespace std;

namespace JOGACO
{
    Personagem::Personagem()
        : Entidade(), maxHealth(1), health(maxHealth), isGrounded(false), characterState(CharacterState::Idle)
    {
    }

    Personagem::Personagem(Vector2f position, int maxHealth, CharacterState state)
        : Entidade(position), maxHealth(maxHealth), health(maxHealth), isGrounded(false), characterState(state)
    {
    }

    Personagem::~Personagem()
    {
    }

    void Personagem::update()
    {
        if (health <= 0)
        {
            death();
        }
    }

    void Personagem::death()
    {
        characterState = CharacterState::Dead;
    }

    void Personagem::getHit(int damage)
    {
        damage = std::max(damage, 0);
        health -= damage;
        if (health <= 0)
        {
            death();
        }
    }

    int Personagem::getHealth() const
    {
        return health;
    }

    int Personagem::getMaxHealth() const
    {
        return maxHealth;
    }

    CharacterState Personagem::getState()
    {
        return CharacterState();
    }

    void Personagem::setState(CharacterState newState)
    {
        switch (characterState)
        {
        case CharacterState::Idle:
        case CharacterState::Running:
            characterState = newState;
            break;
        case CharacterState::Jumping:
        case CharacterState::Falling:
        case CharacterState::Attacking:
        case CharacterState::Hurt:
        case CharacterState::Dying:
        case CharacterState::Dead:
            break;
        default:
            throw std::invalid_argument("Invalid character state");
        }
    }
} // namespace JOGACO