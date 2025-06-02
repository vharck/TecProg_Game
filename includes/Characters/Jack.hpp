#pragma once

#include "Inimigo.hpp"

namespace JOGACO
{
    class Jack : public Inimigo
    {
    public:
        Jack(sf::Vector2f _position, int _maxHealth, int _threatLevel,
             float _chaseSpeed, float _attackRange, int _attackFrames, int _attackCooldownFrames,
             int _jumpFrames, float _jumpForce,
             float _patrolSpeed, sf::Vector2f _detectionBoxSize, sf::Vector2f _patrolStartPosition, sf::Vector2f _patrolEndPosition,
             CharacterState state = CharacterState::Idle);
        ~Jack();

        void becameGrounded();
        void chase();
        void jump();
        void attack();
        void move(const sf::Vector2f &target);
        void update() override;
        void patrol();
    };
}