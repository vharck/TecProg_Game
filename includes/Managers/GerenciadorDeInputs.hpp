#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

namespace JOGACO
{
    class GerenciadorDeInputs
    {
    private:
        float directionalnput;
        bool jumpInput;

        const Keyboard::Key jumpKey;
        const Keyboard::Key leftKey;
        const Keyboard::Key rightKey;

    public:
        GerenciadorDeInputs(Keyboard::Key _jumpKey = Keyboard::Space,
                            Keyboard::Key _leftKey = Keyboard::A,
                            Keyboard::Key _rightKey = Keyboard::D);
        ~GerenciadorDeInputs();

        void processInputEvent(RenderWindow &window);
        float getDirectionalInput();
        bool getJumpInput();
    };
}