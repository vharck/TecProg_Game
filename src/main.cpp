#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Vector>
#include <optional>
#include <iostream>

using namespace sf;
using namespace std;

template <typename T>
T lerp(const T &a, const T &b, float t)
{
    return a + (b - a) * t;
}

template <typename T>
T clamp(const T &value, const T &min, const T &max)
{
    return std::max(min, std::min(max, value));
}

template <typename T>
int sign(const T &value)
{
    return value == 0 ? 1 : (T(0) < value) - (value < T(0));
}

int main()
{
    RenderWindow window(VideoMode({800, 600}), "My window");
    window.setFramerateLimit(60);

    View view = window.getView();

    Event event;

    RectangleShape square(Vector2f(50.f, 50.f));
    square.setOrigin(square.getSize() / 2.f);

    RectangleShape squareYDetection(Vector2f(square.getSize().x, 0.1f));
    squareYDetection.setOrigin(square.getSize().x / 2.f, 0);
    squareYDetection.setPosition(Vector2f(square.getSize().x, 0.f));

    RectangleShape squareXDetection(Vector2f(0.1f, square.getSize().y));
    squareXDetection.setOrigin(0, square.getSize().y / 2.f);
    squareXDetection.setPosition(Vector2f(0.f, square.getSize().y));

    RectangleShape line(Vector2f(800.f, 10.f));
    line.setPosition(0, 10);
    RectangleShape line2(Vector2f(1600.f, 10.f));
    line2.setPosition(-800, 100);
    RectangleShape line3(Vector2f(10.f, 800.f));
    line3.setPosition(-300, -300);
    RectangleShape line4(Vector2f(800.f, 10.f));
    line4.setPosition(0, -200);

    vector<RectangleShape> ground;
    ground.push_back(line);
    ground.push_back(line2);
    ground.push_back(line3);
    ground.push_back(line4);

    float x = 0.f;
    float y = 0.f;

    int frameCountJump = 0;
    bool isJumping = false;
    bool isGrounded = true;

    Vector2f offset(square.getSize().x * 5, -square.getSize().y * 1.5f);

    float xCamera = 0.f;
    Vector2f cameraTarget(0.f, 0.f);
    Vector2f cameraPosition(0.f, 0.f);

    while (window.isOpen())
    {
        window.clear(Color::Black);
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }

        // controle input e movimento do jogador
        if (Keyboard::isKeyPressed(Keyboard::D))
            x = 5.f;
        else if (Keyboard::isKeyPressed(Keyboard::A))
            x = -5.f;
        else
            x = 0.f;

        if (Keyboard::isKeyPressed(Keyboard::Space) && frameCountJump < 30)
        {
            isGrounded = false;
            y = 7.f;
            frameCountJump++;
        }
        else if (frameCountJump >= 30 && frameCountJump < 60)
        {
            y = lerp(y, -10.f, 0.04f);
            frameCountJump++;
        }
        else if (!isGrounded)
            y = lerp(y, -10.f, 0.16f);

        // sistema de detecção de colisão
        squareXDetection.setSize(Vector2f(x, square.getSize().y));
        squareXDetection.setPosition(square.getPosition().x + (sign(x) * square.getSize().x) / 2.f, square.getPosition().y);
        for (int i = 0; i < ground.size(); i++)
        {
            if (squareXDetection.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
            {
                x = 0.f;
                square.move(-x, 0.f);
            }
        }

        squareYDetection.setSize(Vector2f(square.getSize().x, -y + 0.1f));
        squareYDetection.setPosition(square.getPosition().x, square.getPosition().y + (-sign(y) * square.getSize().y) / 2.f);
        bool foundGround = false;
        for (int i = 0; i < ground.size(); i++)
        {
            if (squareYDetection.getGlobalBounds().intersects(ground[i].getGlobalBounds()))
            {
                if (y < 0.f)
                {
                    foundGround = true;
                    y = 0.f;
                }
                else
                {
                    y = 0.f;
                }
            }
        }

        if (foundGround)
        {
            isGrounded = true;
            frameCountJump = 0;
            isJumping = false;
        }
        else
        {
            isGrounded = false;
        }

        square.move(x, -y);

        // controle da câmera
        if (y >= 0)
        {
            cameraTarget.y = square.getPosition().y + offset.y;
            cameraPosition.y = lerp(view.getCenter().y, cameraTarget.y, 0.04f);
        }
        else
        {
            cameraTarget.y = square.getPosition().y - (offset.y * 2.f);
            cameraPosition.y = lerp(view.getCenter().y, cameraTarget.y, 0.02f);
        }

        if (x == 0)
        {
            cameraTarget.x = square.getPosition().x;
            cameraPosition.x = lerp(view.getCenter().x, cameraTarget.x, 0.02f);
        }
        else
        {
            cameraTarget.x = square.getPosition().x + (x > 0 ? offset.x : -offset.x);
            cameraPosition.x = lerp(view.getCenter().x, cameraTarget.x, 0.075f);
        }

        view.setCenter(cameraPosition);

        window.setView(view);
        window.draw(square);
        for (const auto &g : ground)
        {
            window.draw(g);
        }

        window.display();
    }

    return 0;
}