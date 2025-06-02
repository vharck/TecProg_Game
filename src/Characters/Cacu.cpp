#include "Cacu.hpp"
#include "Jogador.hpp"

#include "Utilidade.hpp"

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
            int randomValue = Utilidade::random(0, 9);

            if (randomValue < 1)
            {
                currentAction = CacuAction::Jumping;
                actionFrameCounter = Utilidade::random(60, 90);
            }
            else if (randomValue < 7)
            {
                currentAction = CacuAction::Moving;
                move(targetPlayer->getPosition());
                actionFrameCounter = Utilidade::random(120, 150);
            }
            else
            {
                currentAction = CacuAction::Attacking;
                actionFrameCounter = Utilidade::random(90, 120);
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
        // precisa fazer o projetil antes de fazer o ataque dele
        // mas vai ser basicamente uma bola de fogo que viaja quicando no chão tipo em seno só que só positivo
        // e outro ataque que ele da um tapão no chão e joga tudo pra cima
        // um outro ataque dele, bem baixo a chance de acontecer, ele joga um jack no player
        // esse jack é vermelho e fica só correndo atrás do player
    }

    void Cacu::move(const sf::Vector2f &target)
    {
        // tem que ver a questão do movimento que a velocidade dele é meio aleatória
        // dai ele anda rápido pracima do player e fica lento depois
        // ele corre atrás do player mas não sai da área de patrulha
    }

    void Cacu::update()
    {
        // só roda tudo
    }

    void Cacu::patrol()
    {

        setState(CharacterState::Idle);
    }
} // namespace JOGACO