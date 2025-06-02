#include "Inimigo.hpp"

#include <random>

namespace JOGACO
{
    class Cacu : public Inimigo
    {
    protected:
        enum class CacuAction
        {
            Idle,
            Jumping,
            Attacking,
            Moving
        };

        CacuAction currentAction;

        int actionFrameCounter;

    public:
        Cacu(sf::Vector2f _position, int _maxHealth, int _threatLevel,
             float _chaseSpeed, float _attackRange, int _attackFrames, int _attackCooldownFrames,
             int _jumpFrames, float _jumpForce,
             float _patrolSpeed, sf::Vector2f _detectionBoxSize, sf::Vector2f _patrolStartPosition, sf::Vector2f _patrolEndPosition,
             CharacterState state = CharacterState::Idle);
        ~Cacu();

        void becameGrounded() override;
        void chase() override;
        void jump() override;
        void attack() override;
        void move(const sf::Vector2f &target);
        void update() override;
        void patrol() override;
    };
} // namespace JOGACO