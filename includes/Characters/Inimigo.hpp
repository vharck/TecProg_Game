#pragma once

#include "Personagem.hpp"

#include <Vector>

using namespace sf;

namespace JOGACO
{
    class Jogador;

    class Inimigo : public Personagem
    {
    protected:
        const int threatLevel;

        const float patrolSpeed;
        const float chaseSpeed;

        const float attackRange;
        const int attackFrames;
        int currentAttackFrame;
        const int attackCooldownFrames;
        int attackCooldownCounter;

        const int jumpFrames;
        int currentJumpFrame;
        const float jumpForce;

        const Vector2f patrolStartPosition;
        const Vector2f patrolEndPosition;
        Vector2f currentPatrolTarget;
        Vector2f lastKnownPlayerPosition;
        const Vector2f detectionBoxSize;
        bool isPlayerInView = false;

        vector<Jogador *> detectedPlayers;

        Jogador *targetPlayer;

        Gerenciadores::GerenciadorColisoes::Trigger *attackTrigger;
        Gerenciadores::GerenciadorColisoes::Trigger *detectionTrigger;

    protected:
        virtual void searchForPlayer(const Jogador *targetPlayer);
        virtual void searchForPlayer();
        virtual void considerTarget();

        virtual void onDamageTriggerEnter(Gerenciadores::GerenciadorColisoes::Collider *other);
        virtual void onDetectionTriggerEnter(Gerenciadores::GerenciadorColisoes::Collider *other);
        virtual void onDetectionTriggerExit(Gerenciadores::GerenciadorColisoes::Collider *other);

        virtual void jump();

        virtual void chase() = 0;
        virtual void patrol() = 0;
        virtual void move() = 0;
        virtual void attack() = 0;

    public:
        Inimigo(Vector2f _position, int _maxHealth, int _threatLevel,
                float _chaseSpeed, float _attackRange, int _attackFrames, int _attackCooldownFrames,
                int _jumpFrames, float _jumpForce,
                float _patrolSpeed, Vector2f _detectionBoxSize, Vector2f _patrolStartPosition, Vector2f _patrolEndPosition,
                CharacterState state = CharacterState::Idle);
        virtual ~Inimigo();

        virtual void becameGrounded();

        virtual void update() override;
    };
}