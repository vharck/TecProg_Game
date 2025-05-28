#include "Jogador.hpp"

using namespace sf;
using namespace std;
namespace JOGACO
{
    Jogador::Jogador(Vector2f position, int maxHealth, CharacterState state, Keyboard::Key jumpKey, Keyboard::Key leftKey, Keyboard::Key rightKey)
        : Personagem(position, maxHealth, state), GerenciadorDeInputs(jumpKey, leftKey, rightKey)
    {
    }

    Jogador::~Jogador()
    {
    }

    void Jogador::move(Vector2f direction)
    {
        float directionalInput = inputManager.getDirectionalInput();
        if (directionalInput != 0.0f)
        {
            Vector2f moveDirection = Vector2f(directionalInput * 0.16f * 20.f, moveDirection.y);
            if (getState() == CharacterState::Idle)
                setState(CharacterState::Running);
        }
        else
        {
        }

        if (inputManager.getJumpInput())
        {
            jump();
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