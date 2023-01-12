#include <SFML/Graphics.hpp>

// clang++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib  -lsfml-graphics -lsfml-window -lsfml-system -std=c++20
using namespace sf;

const unsigned int WIDTH = 1300;
const unsigned int HEIGHT = 1000;
const unsigned int PADDLE_W = 35;
const unsigned int PADDLE_H = 150;


int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong!");
    // paddle for the bot
    sf::RectangleShape bot_paddle(Vector2f(PADDLE_W,PADDLE_H));
    bot_paddle.setFillColor(sf::Color::White);
    bot_paddle.setPosition(Vector2f(35, (HEIGHT - PADDLE_H) / 2));

    // make paddle for the player
    sf::RectangleShape player_paddle(Vector2f(PADDLE_W,PADDLE_H));
    player_paddle.setFillColor(sf::Color::White);
    player_paddle.setPosition(Vector2f(WIDTH - 70, (HEIGHT - PADDLE_H) / 2));

    // draw out the lines in the middle of the board

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(bot_paddle);
        window.draw(player_paddle);
        window.display();
    }

    return 0;
}
