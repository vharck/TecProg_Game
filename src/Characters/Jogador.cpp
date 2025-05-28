#include "Jogador.hpp"
#include "Utilidade.hpp"

using namespace sf;
using namespace std;
using namespace JOGACO::Utilidade;

namespace JOGACO
{
    Jogador::Jogador(Vector2f position, int maxHealth, CharacterState state, Keyboard::Key jumpKey, Keyboard::Key leftKey, Keyboard::Key rightKey)
        : Personagem(position, maxHealth, state), GerenciadorDeInputs(jumpKey, leftKey, rightKey),
          maxRunSpeed(20.f), jumpForce(15.f), acceleration(0.5f), deceleration(0.5f),
          maxCoyoteFrames(10), maxJumpBufferFrames(10), maxJumpHoldFrames(10),
          coyoteFCount(0), jumpBufferFCount(0), jumpHoldFCount(0), currentRunSpeed(0.f)
    {
    }

    Jogador::Jogador()
        : Personagem(), GerenciadorDeInputs(),
          maxRunSpeed(20.f), jumpForce(15.f), acceleration(0.5f), deceleration(0.5f),
          maxCoyoteFrames(10), maxJumpBufferFrames(10), maxJumpHoldFrames(10),
          coyoteFCount(0), jumpBufferFCount(0), jumpHoldFCount(0), currentRunSpeed(0.f)
    {
    }

    Jogador::~Jogador()
    {
    }

    void Jogador::move()
    {
        float directionalInput = getDirectionalInput();
        if (directionalInput != 0.0f)
        {
            if (isGrounded)
            {
                if (sign(directionalInput) != sign(currentRunSpeed))
                    currentRunSpeed = moveTowards(currentRunSpeed, directionalInput * maxRunSpeed, deceleration * timeStep);
                else
                    currentRunSpeed = moveTowards(currentRunSpeed, directionalInput * maxRunSpeed, acceleration * timeStep);
            }
            else
            {
                // movimento no ar
            }
            setState(CharacterState::Running);
        }
        else
        {
            currentRunSpeed = moveTowards(currentRunSpeed, 0.f, deceleration * timeStep);
            setState(CharacterState::Idle);
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

            if ((getState() == CharacterState::Idle || getState() == CharacterState::Running))
            {
            }
            else if (getState() == CharacterState::Jumping)
            {
                if (jumpHoldFCount < maxJumpHoldFrames)
                {
                    jumpHoldFCount++;
                }
            }
        }
    }

    void Jogador::jump()
    {
        // Implement jump logic here
    }

    void Jogador::update()
    {

        // Call base class update
        Personagem::update();
    }
}