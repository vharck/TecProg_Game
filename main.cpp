#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
    window.setFramerateLimit(60);

    sf::Event event;

    sf::RectangleShape square(sf::Vector2f(100.f, 100.f));
    sf::RectangleShape line(sf::Vector2f(800.f, 10.f));
    line.setPosition(0, 500);

    while (window.isOpen())
    {
        window.clear(sf::Color::Black);
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            square.move(5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            square.move(-5.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            square.move(0.f, -10.f);
        }

        square.move(0.f, 5.f);

        if (line.getGlobalBounds().intersects(square.getGlobalBounds()))
        {
            square.move(0.f, -5.f);
        }

        window.draw(square);
        window.draw(line);

        window.display();
    }

    return 0;
}