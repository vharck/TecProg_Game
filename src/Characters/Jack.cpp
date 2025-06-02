#include "Jack.hpp"

#include "Utilidade.hpp"
#include "GerenciadorColisoes.hpp"

#include "Jogador.hpp"

namespace JOGACO
{
    using namespace Gerenciadores;

    Jack::Jack(sf::Vector2f _position, int _maxHealth, int _threatLevel,
               float _chaseSpeed, float _attackRange, int _attackFrames, int _attackCooldownFrames,
               int _jumpFrames, float _jumpForce,
               float _patrolSpeed, sf::Vector2f _detectionBoxSize, sf::Vector2f _patrolStartPosition, sf::Vector2f _patrolEndPosition,
               CharacterState state)
        : Inimigo(_position, _maxHealth, _threatLevel, _chaseSpeed, _attackRange, _attackFrames, _attackCooldownFrames,
                  _jumpFrames, _jumpForce, _patrolSpeed, _detectionBoxSize, _patrolStartPosition, _patrolEndPosition, state)
    {
    }

    Jack::~Jack()
    {
    }

    void Jack::becameGrounded()
    {
        Inimigo::becameGrounded();
    }

    void Jack::chase()
    {
        if (isPlayerInView)
        {
            considerTarget();
            if (targetPlayer)
            {
                lastKnownPlayerPosition = targetPlayer->getPosition();

                if (abs(lastKnownPlayerPosition.x - getPosition().x) < attackRange && (abs(lastKnownPlayerPosition.y - getPosition().y) < attackRange))
                {
                    setState(CharacterState::Attacking);
                    attack();
                }
                else
                {
                    setState(CharacterState::Chasing);
                    move(lastKnownPlayerPosition);
                }
            }
        }
        else
        {
            searchForPlayer();
        }
    }

    void Jack::jump()
    {
        Inimigo::jump();
    }

    void Jack::attack()
    {
        if (targetPlayer)
        {
            if (currentAttackFrame < attackFrames)
            {
                currentAttackFrame++;
            }
            else
            {
                currentAttackFrame = 0;
                attackCooldownCounter = 0;
                setState(CharacterState::Idle);
            }
        }
    }

    void Jack::move(const sf::Vector2f &target)
    {
        sf::Vector2f direction = target - getPosition();

        switch (getState())
        {
        case CharacterState::Chasing:
            if (targetPlayer)
            {
                currentRunSpeed = Utilidade::moveTowards(currentRunSpeed, direction.x, chaseSpeed * Utilidade::timeStep);

                if (abs(target.y - getPosition().y) > jumpForce)
                {
                    if (isGrounded)
                    {
                        setState(CharacterState::Jumping);
                        currentAirSpeed = -jumpForce * Utilidade::timeStep;
                    }
                }
            }
            else
                searchForPlayer();
            break;
        case CharacterState::Jumping:
        case CharacterState::Falling:
        case CharacterState::Patrolling:
            currentRunSpeed = Utilidade::moveTowards(currentRunSpeed, direction.x, patrolSpeed * Utilidade::timeStep);
            break;
        }
    }

    void Jack::patrol()
    {
        if (currentPatrolTarget == patrolStartPosition)
            currentPatrolTarget = patrolEndPosition;
        else
            currentPatrolTarget = patrolStartPosition;

        if (abs(currentPatrolTarget.y - getPosition().y) > jumpForce)
        {
            if (isGrounded)
            {
                setState(CharacterState::Jumping);
                jump();
            }
        }

        move(currentPatrolTarget);
    }
}