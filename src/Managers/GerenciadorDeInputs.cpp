#include "GerenciadorDeInputs.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

namespace JOGACO
{
    GerenciadorDeInputs::GerenciadorDeInputs(Keyboard::Key _jumpKey, Keyboard::Key _leftKey, Keyboard::Key _rightKey)
        : directionalnput(0.0f), jumpInput(false), jumpKey(_jumpKey), leftKey(_leftKey), rightKey(_rightKey)
    {
    }

    GerenciadorDeInputs::~GerenciadorDeInputs()
    {
    }

    void GerenciadorDeInputs::processInputEvent(RenderWindow &window)
    {
        directionalnput = 0.0f;
        jumpInput = false;

        Event event;
        window.pollEvent(event);

        switch (event.type)
        {
        case Event::KeyPressed:
            if (event.key.code == leftKey)
            {
                directionalnput = -1.0f;
            }
            else if (event.key.code == rightKey)
            {
                directionalnput = 1.0f;
            }
            else if (event.key.code == jumpKey)
            {
                jumpInput = true;
            }
            break;

        case Event::KeyReleased:
            if (event.key.code == leftKey || event.key.code == rightKey)
            {
                directionalnput = 0.0f;
            }
            else if (event.key.code == jumpKey)
            {
                jumpInput = false;
            }
            break;
        }
    }

    float GerenciadorDeInputs::getDirectionalInput()
    {
        return directionalnput;
    }

    bool GerenciadorDeInputs::getJumpInput()
    {
        return jumpInput;
    }
}