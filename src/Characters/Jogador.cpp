#include "Jogador.hpp"
#include "Utilidade.hpp"

using namespace sf;
using namespace std;
using namespace JOGACO::Utilidade;

namespace JOGACO
{
    Jogador::Jogador(Vector2f position, int maxHealth, CharacterState state, Keyboard::Key jumpKey, Keyboard::Key leftKey, Keyboard::Key rightKey)
        : Personagem(position, maxHealth, state), GerenciadorDeInputs(jumpKey, leftKey, rightKey),
          maxRunSpeed(20.f), jumpForce(15.f), acceleration(0.5f), deceleration(0.5f), airControlFactor(0.5f),
          maxCoyoteFrames(10), maxJumpBufferFrames(10), maxJumpHoldFrames(10),
          coyoteFCount(0), jumpBufferFCount(0), jumpHoldFCount(0),
          jumpOnBuffer(false), hasJumpEndedEarly(false)
    {
    }

    Jogador::Jogador()
        : Personagem(), GerenciadorDeInputs(),
          maxRunSpeed(20.f), jumpForce(15.f), acceleration(0.5f), deceleration(0.5f),
          maxCoyoteFrames(10), maxJumpBufferFrames(10), maxJumpHoldFrames(10), airControlFactor(0.5f),
          coyoteFCount(0), jumpBufferFCount(0), jumpHoldFCount(0),
          jumpOnBuffer(false), hasJumpEndedEarly(false)
    {
    }

    Jogador::~Jogador()
    {
    }

    void Jogador::move()
    {
        float directionalInput = getDirectionalInput();
        if (isGrounded)
        {
            if (directionalInput != 0.0f)
            {

                if (sign(directionalInput) != sign(currentRunSpeed))
                    currentRunSpeed = moveTowards(currentRunSpeed, directionalInput * maxRunSpeed, deceleration * timeStep);
                else
                    currentRunSpeed = moveTowards(currentRunSpeed, directionalInput * maxRunSpeed, acceleration * timeStep);
                setState(CharacterState::Running);
            }
            else
            {
                currentRunSpeed = moveTowards(currentRunSpeed, 0.f, deceleration * timeStep);
                setState(CharacterState::Idle);
            }
        }
        else
        {
            currentRunSpeed = moveTowards(currentRunSpeed, directionalInput * maxRunSpeed, acceleration * airControlFactor * timeStep);
        }

        if (getJumpInput())
        {

            switch (getState())
            {
            case CharacterState::Idle:
            case CharacterState::Running:
                if (isGrounded || coyoteFCount < maxCoyoteFrames)
                {
                    jump();
                    isGrounded = false;
                    setState(CharacterState::Jumping);
                }
                break;
            case CharacterState::Jumping:
                if (jumpHoldFCount < maxJumpHoldFrames)
                    jumpHoldFCount++;
                else
                    setState(CharacterState::Falling);
                break;
            case CharacterState::Falling:
                if (jumpOnBuffer)
                    jumpBufferFCount = 0;
                else
                    jumpOnBuffer = true;
                break;

            default:
                break;
            }
        }
        else if (getState() == CharacterState::Jumping)
        {
            if (jumpHoldFCount < maxJumpHoldFrames)
            {
                hasJumpEndedEarly = true;
                setState(CharacterState::Falling);
            }
        }
    }

    void Jogador::jump()
    {
        switch (getState())
        {
        case CharacterState::Jumping:
            currentAirSpeed = -gravity * timeStep;
            currentAirSpeed += jumpForce * timeStep;
            break;

        case CharacterState::Falling:
            if (!hasJumpEndedEarly)
                currentAirSpeed = moveTowards(currentAirSpeed, 0, gravity * timeStep);
            else
                currentAirSpeed = gravity * timeStep;
            break;

        default:
            return;
        }
    }

    void Jogador::becameGrounded()
    {
        isGrounded = true;
        coyoteFCount = 0;
        jumpHoldFCount = 0;

        if (jumpOnBuffer && jumpBufferFCount < maxJumpBufferFrames)
        {
            jumpOnBuffer = false;
            jumpBufferFCount = 0;
            jump();
            if (getState() == CharacterState::Jumping || getState() == CharacterState::Falling)
                getState() == CharacterState::Jumping;
        }
        else
        {
            if (getState() == CharacterState::Jumping || getState() == CharacterState::Falling)
                currentRunSpeed != 0.f ? setState(CharacterState::Running) : setState(CharacterState::Idle);
        }
    }

    void Jogador::update()
    {

        if (!isGrounded && coyoteFCount < maxCoyoteFrames)
            coyoteFCount++;
        if (jumpOnBuffer && jumpBufferFCount < maxJumpBufferFrames)
            jumpBufferFCount++;
        if (getState() == CharacterState::Jumping)
        {
            if (jumpHoldFCount < maxJumpHoldFrames)
                jumpHoldFCount++;
            else
            {
                hasJumpEndedEarly = false;
                setState(CharacterState::Falling);
            }
        }

        move();
        if (getState() == CharacterState::Jumping || getState() == CharacterState::Falling)
            jump();

        setPosition(getPosition() + Vector2f(currentRunSpeed, currentAirSpeed));
        Personagem::update();
    }
}