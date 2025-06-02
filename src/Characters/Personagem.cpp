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
        : Entidade(position), maxHealth(maxHealth), health(maxHealth),
          isGrounded(false), currentAirSpeed(0.f), currentRunSpeed(0.f),
          characterState(state)
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
        case CharacterState::Attacking:
        case CharacterState::Hurt:
            characterState = newState;
            break;
        case CharacterState::Jumping:
        case CharacterState::Falling:
            if (newState == CharacterState::Idle || newState == CharacterState::Running)
                if (!isGrounded)
                    break;
                else
                    characterState = newState;
            break;
        case CharacterState::Dying:
            if (newState == CharacterState::Dead)
            {
                characterState = CharacterState::Dead;
            }
            else
            {
                throw invalid_argument("Cannot change state from Dying to " + to_string(static_cast<int>(newState)) + ", collisions should be ignored during dying animations!");
            }
            break;
        case CharacterState::Dead:
            throw invalid_argument("Cannot change state from Dead to " + to_string(static_cast<int>(newState)) + ", collisions should be ignored!");
            break;
        default:
            throw invalid_argument("Invalid character state");
        }
    }
} // namespace JOGACO