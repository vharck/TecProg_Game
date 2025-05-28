// Character
#pragma once
#include <SFML/Graphics.hpp>
#include "Entidade.hpp"

using namespace sf;
using namespace std;
namespace JOGACO
{
    enum class CharacterState
    {
        Idle,
        Running,
        Jumping,
        Falling,
        Attacking,
        Hurt,
        Dying,
        Dead
    };

    class Personagem : public Entidade
    {
    private:
        CharacterState characterState;

    protected:
        int maxHealth;
        int health;
        bool isGrounded;

    private:
        virtual void death();

    public:
        Personagem();
        Personagem(Vector2f position, int maxHealth, CharacterState state = CharacterState::Idle);
        virtual ~Personagem();

        virtual void move(Vector2f direction);
        virtual void update();

        void getHit(int damage);

        int getHealth() const;
        int getMaxHealth() const;
        CharacterState getState();
        void setState(CharacterState newState);
    };
}