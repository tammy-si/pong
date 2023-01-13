#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// clang++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib  -lsfml-graphics -lsfml-window -lsfml-system -std=c++20
using namespace sf;
using namespace std;

const unsigned int WIDTH = 1300;
const unsigned int HEIGHT = 1000;
const unsigned int PADDLE_W = 35;
const unsigned int PADDLE_H = 150;


int main()
{
    int curr_height =  (HEIGHT - PADDLE_H) / 2;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong!");
    // limit frame rate
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("VCR_OSD_MONO_1.001.ttf");
    // paddle for the bot
    sf::RectangleShape bot_paddle(Vector2f(PADDLE_W,PADDLE_H));
    bot_paddle.setFillColor(sf::Color::White);

    // make paddle for the player
    sf::RectangleShape player_paddle(Vector2f(PADDLE_W,PADDLE_H));
    player_paddle.setFillColor(sf::Color::White);

    // player score and bot score start at zero
    int player_score = 0;
    int bot_score = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            // check to make sure it's not out of bounds
            if (curr_height > 0) {
            // up key is pressed: move paddle up
                curr_height -= 10;

            }
        } 
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (curr_height < 850){
                curr_height += 10;
            }
        }

        window.clear();
        window.draw(bot_paddle);
        window.draw(player_paddle);
        bot_paddle.setPosition(Vector2f(35, curr_height));
        player_paddle.setPosition(Vector2f(WIDTH - 70, curr_height));   
        // draw out the lines in the middle of the board
        for (int i = 0; i <= HEIGHT; i += 75) {
            sf::RectangleShape square(Vector2f(25,25));
            square.setFillColor(sf::Color::White);
            square.setPosition((WIDTH - 25) / 2, i);
            window.draw(square);
        }
        // draw out the bot score
        sf::Text bot_score_display;
        bot_score_display.setString(to_string(bot_score));
        bot_score_display.setFont(font);
        bot_score_display.setFillColor(sf::Color::White);
        bot_score_display.setPosition(525, 25);
        bot_score_display.setCharacterSize(75);
        window.draw(bot_score_display);
        // draw out the player score
        sf::Text player_score_display;
        player_score_display.setString(to_string(bot_score));
        player_score_display.setFont(font);
        player_score_display.setFillColor(sf::Color::White);
        player_score_display.setPosition(725, 25);
        player_score_display.setCharacterSize(75);
        window.draw(player_score_display);
        window.display();
    }

    return 0;
}
