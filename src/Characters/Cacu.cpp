#include "Cacu.hpp"
#include "Jogador.hpp"

#include <random>

namespace JOGACO
{
    Cacu::Cacu(sf::Vector2f _position, int _maxHealth, int _threatLevel,
               float _chaseSpeed, float _attackRange, int _attackFrames, int _attackCooldownFrames,
               int _jumpFrames, float _jumpForce,
               float _patrolSpeed, sf::Vector2f _detectionBoxSize, sf::Vector2f _patrolStartPosition, sf::Vector2f _patrolEndPosition,
               CharacterState state)
        : Inimigo(_position, _maxHealth, _threatLevel, _chaseSpeed, _attackRange, _attackFrames, _attackCooldownFrames,
                  _jumpFrames, _jumpForce, _patrolSpeed, _detectionBoxSize, _patrolStartPosition, _patrolEndPosition, state),
          actionFrameCounter(0), currentAction(CacuAction::Idle)
    {
    }

    Cacu::~Cacu() {}

    int Cacu::random(int min, int max)
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    void Cacu::becameGrounded()
    {
        currentJumpFrame = 0;
    }

    void Cacu::chase()
    {
        if (!targetPlayer)
            return;
        if (actionFrameCounter <= 0)
        {
            int randomValue = random(0, 9);

            if (randomValue < 1)
            {
                currentAction = CacuAction::Jumping;
                actionFrameCounter = random(60, 90);
            }
            else if (randomValue < 7)
            {
                currentAction = CacuAction::Moving;
                move(targetPlayer->getPosition());
                actionFrameCounter = random(120, 150);
            }
            else
            {
                currentAction = CacuAction::Attacking;
                actionFrameCounter = random(90, 120);
            }
        }

        switch (currentAction)
        {
        case CacuAction::Attacking:
            if (attackCooldownCounter >= attackCooldownFrames || attackCooldownFrames <= 0)
            {
                setState(CharacterState::Attacking);
                attack();
                attackCooldownCounter = 0;
            }

            if (actionFrameCounter < attackFrames)
            {
                actionFrameCounter++;
                attack();
            }
            break;
        case CacuAction::Jumping:
            if (isGrounded)
            {
                setState(CharacterState::Jumping);
            }
            jump();
            if (getState() == CharacterState::Jumping)
                move(targetPlayer->getPosition());
            break;
        case CacuAction::Moving:
            move(targetPlayer->getPosition());
        }

        actionFrameCounter--;
    }

    void Cacu::jump()
    {
        setState(CharacterState::Idle);
    }

    void Cacu::attack()
    {
    }

    void Cacu::move(const sf::Vector2f &target)
    {
    }

    void Cacu::update()
    {
    }

    void Cacu::patrol()
    {
        setState(CharacterState::Idle);
    }
} // namespace JOGACO