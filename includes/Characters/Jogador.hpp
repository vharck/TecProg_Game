#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Personagem.hpp"
#include "GerenciadorDeInputs.hpp"

using namespace sf;
using namespace std;
namespace JOGACO
{
    class Jogador : public Personagem, public GerenciadorDeInputs
    {
    private:
        GerenciadorDeInputs inputManager;

    public:
        Jogador(Vector2f position, int maxHealth,
                CharacterState state = CharacterState::Idle,
                Keyboard::Key jumpKey = Keyboard::Space,
                Keyboard::Key leftKey = Keyboard::A,
                Keyboard::Key rightKey = Keyboard::D);
        virtual ~Jogador();

        void move(Vector2f direction);
        void jump();

        void update();
    };
}