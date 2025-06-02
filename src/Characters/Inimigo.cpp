#include "Inimigo.hpp"

#include "Jogador.hpp"
#include "Utilidade.hpp"

#include "GerenciadorColisoes.hpp"

#include <vector>
#include <algorithm>

namespace JOGACO
{
    Inimigo::Inimigo(sf::Vector2f _position, int _maxHealth, int _threatLevel,
                     float _chaseSpeed, float _attackRange, int _attackFrames, int _attackCooldownFrames,
                     int _jumpFrames, float _jumpForce,
                     float _patrolSpeed, sf::Vector2f _detectionBoxSize, sf::Vector2f _patrolStartPosition, sf::Vector2f _patrolEndPosition,
                     CharacterState state)
        : Personagem(_position, _maxHealth, state), threatLevel(_threatLevel),
          patrolSpeed(_patrolSpeed), chaseSpeed(_chaseSpeed), attackRange(_attackRange),
          attackFrames(_attackFrames), currentAttackFrame(0), attackCooldownFrames(_attackCooldownFrames), attackCooldownCounter(0),
          jumpFrames(_jumpFrames), currentJumpFrame(0), jumpForce(_jumpForce),
          patrolStartPosition(_patrolStartPosition), patrolEndPosition(_patrolEndPosition),
          currentPatrolTarget(_patrolStartPosition), lastKnownPlayerPosition(sf::Vector2f(0.f, 0.f)),
          detectionBoxSize(_detectionBoxSize), targetPlayer(nullptr)
    {
        detectionTrigger = new Gerenciadores::GerenciadorColisoes::Trigger(this, _position, detectionBoxSize, Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer::Player);
        attackTrigger = new Gerenciadores::GerenciadorColisoes::Trigger(this, _position, Vector2f(attackRange, attackRange), Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer::Player);

        detectionTrigger->subscribeToCollisionExit(this, &Inimigo::onDetectionTriggerExit);
        detectionTrigger->subscribeToCollisionEnter(this, &Inimigo::onDetectionTriggerEnter);

        attackTrigger->subscribeToCollisionEnter(this, &Inimigo::onDamageTriggerEnter);
    }

    Inimigo::~Inimigo()
    {
        detectionTrigger->unsubscribeFromCollisionExit(this, &Inimigo::onDetectionTriggerExit);
        detectionTrigger->unsubscribeFromCollisionEnter(this, &Inimigo::onDetectionTriggerEnter);

        attackTrigger->unsubscribeFromCollisionEnter(this, &Inimigo::onDamageTriggerEnter);

        delete detectionTrigger;
        delete attackTrigger;
        detectionTrigger = nullptr;
        attackTrigger = nullptr;
    }

    void Inimigo::searchForPlayer(const Jogador *_targetPlayer)
    {
        if (_targetPlayer)
        {
            lastKnownPlayerPosition = _targetPlayer->getPosition();
            if (std::find(detectedPlayers.begin(), detectedPlayers.end(), _targetPlayer) == detectedPlayers.end())
                detectedPlayers.push_back(const_cast<Jogador *>(_targetPlayer));
        }
        else
        {
            isPlayerInView = false;
            targetPlayer = nullptr;
        }
    }

    void Inimigo::searchForPlayer()
    {
    }

    void Inimigo::considerTarget()
    {
        switch (detectedPlayers.size())
        {
        case 0:
            isPlayerInView = false;
            targetPlayer = nullptr;
            break;
        case 1:
            targetPlayer = detectedPlayers[0];
            lastKnownPlayerPosition = targetPlayer->getPosition();
            isPlayerInView = true;
            break;
        case 2:
            Jogador *closestPlayer = detectedPlayers[0];
            if (Utilidade::distance(closestPlayer->getPosition(), getPosition()) > Utilidade::distance(detectedPlayers[1]->getPosition(), getPosition()))
            {
                closestPlayer = detectedPlayers[1];
            }
            targetPlayer = closestPlayer;
            lastKnownPlayerPosition = targetPlayer->getPosition();
            isPlayerInView = true;
            break;

        default:
            break;
        }
    }

    void Inimigo::onDamageTriggerEnter(Gerenciadores::GerenciadorColisoes::Collider *other)
    {
        // REQ trycatch
        try
        {
            Personagem *player = dynamic_cast<Personagem *>(other->getParrentEntity());
            if (player)
            {
                player->getHit(1);
            }
        }
        catch (const std::bad_cast &e)
        {
            // Se não for um personagem, não faz nada
        }
    }

    void Inimigo::onDetectionTriggerEnter(Gerenciadores::GerenciadorColisoes::Collider *other)
    {
        try
        {
            Jogador *player = dynamic_cast<Jogador *>(other->getParrentEntity());
            if (player)
            {
                if (std::find(detectedPlayers.begin(), detectedPlayers.end(), player) == detectedPlayers.end())
                    detectedPlayers.push_back(player);

                isPlayerInView = true;
                if (!targetPlayer)
                    targetPlayer = player;
                else
                {
                    considerTarget();
                    lastKnownPlayerPosition = targetPlayer->getPosition();
                }
            }
        }
        catch (const std::bad_cast &e)
        {
            targetPlayer = nullptr;
        }
    }

    void Inimigo::onDetectionTriggerExit(Gerenciadores::GerenciadorColisoes::Collider *other)
    {
        try
        {
            Jogador *player = dynamic_cast<Jogador *>(other->getParrentEntity());
            if (player)
            {
                if (detectedPlayers.size() > 0)
                {
                    auto it = std::remove(detectedPlayers.begin(), detectedPlayers.end(), player);
                    if (it != detectedPlayers.end())
                        detectedPlayers.erase(it);
                }
                if (detectedPlayers.size() == 0)
                {
                    isPlayerInView = false;
                    targetPlayer = nullptr;
                }
                else
                {
                    considerTarget();
                    lastKnownPlayerPosition = targetPlayer->getPosition();
                }
            }
        }
        catch (const std::bad_cast &e)
        {
            // Se não for um jogador, não faz nada
        }
    }

    void Inimigo::jump()
    {
        switch (getState())
        {
        case CharacterState::Jumping:
            if (isGrounded)
            {
                isGrounded = false;
                currentJumpFrame = 0;
                currentAirSpeed = Utilidade::moveTowards(currentAirSpeed, -jumpForce, Utilidade::timeStep * jumpForce);
            }
            else if (currentJumpFrame < jumpFrames)
            {
                currentJumpFrame++;
                currentAirSpeed = Utilidade::moveTowards(currentAirSpeed, -jumpForce, Utilidade::timeStep * jumpForce);
            }
            else
            {
                setState(CharacterState::Falling);
                currentJumpFrame = 0;
            }
            break;
        case CharacterState::Falling:
            currentAirSpeed = Utilidade::moveTowards(currentAirSpeed, 0, gravity * Utilidade::timeStep);
        }
    }

    void Inimigo::patrol()
    {
    }

    void Inimigo::becameGrounded()
    {
        isGrounded = true;
        currentJumpFrame = 0;
        setState(CharacterState::Idle);
    }

    void Inimigo::update()
    {
        Personagem::update();

        switch (getState())
        {
        case CharacterState::Patrolling:
            patrol();
            break;
        case CharacterState::Chasing:
            if (targetPlayer)
            {
                if (abs(targetPlayer->getPosition().x - getPosition().x) < attackRange && (abs(targetPlayer->getPosition().y - getPosition().y) < attackRange))
                    attack();
                else
                    chase();
            }
            break;
        case CharacterState::Falling:
        case CharacterState::Jumping:
            jump();
            break;

        case CharacterState::Attacking:
            if (currentAttackFrame < attackFrames)
            {
                currentAttackFrame++;
                attack();
            }
            else
            {
                currentAttackFrame = 0;
                attackCooldownCounter = 0;
                setState(CharacterState::Idle);
            }
            break;
        }
    }
}
