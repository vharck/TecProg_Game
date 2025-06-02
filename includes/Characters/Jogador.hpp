#pragma once

#include "Personagem.hpp"
#include "GerenciadorDeInputs.hpp"

using namespace sf;
using namespace std;
namespace JOGACO
{
    class Jogador : public Personagem, public GerenciadorDeInputs
    {
    private:
        const float maxRunSpeed;
        const float jumpForce;
        const float acceleration;
        const float deceleration;
        const float airControlFactor;

        const int maxCoyoteFrames;
        const int maxJumpBufferFrames;
        const int maxJumpHoldFrames;

        int coyoteFCount;
        int jumpBufferFCount;
        bool jumpOnBuffer;
        int jumpHoldFCount;
        bool hasJumpEndedEarly;

    public:
        Jogador(Vector2f position, int maxHealth,
                CharacterState state = CharacterState::Idle,
                Keyboard::Key jumpKey = Keyboard::Space,
                Keyboard::Key leftKey = Keyboard::A,
                Keyboard::Key rightKey = Keyboard::D);

        Jogador();
        virtual ~Jogador();

        void move();
        void jump();
        void becameGrounded();

        void update();
    };
}