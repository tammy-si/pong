#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// clang++ main.cpp -I/opt/homebrew/Cellar/sfml/2.5.1_2/include/ -L/opt/homebrew/Cellar/sfml/2.5.1_2/lib  -lsfml-graphics -lsfml-window -lsfml-system -std=c++20
using namespace sf;
using namespace std;

const int WIDTH = 1300;
const int HEIGHT = 1000;
const int PADDLE_W = 35;
const int PADDLE_H = 150;

int main()
{
    int curr_height =  (HEIGHT - PADDLE_H) / 2;
    int bot_height = (HEIGHT - PADDLE_H) / 2;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pong!");
    // limit frame rate
    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("VCR_OSD_MONO_1.001.ttf");
    // paddle for the bot
    sf::RectangleShape bot_paddle(Vector2f(PADDLE_W, PADDLE_H));
    bot_paddle.setFillColor(sf::Color::White);

    // make paddle for the player
    sf::RectangleShape player_paddle(Vector2f(PADDLE_W, PADDLE_H));
    player_paddle.setFillColor(sf::Color::White);

    // player score and bot score start at zero
    int player_score = 0;
    int bot_score = 0;

    // for the ball
    sf::RectangleShape ball(Vector2f(25,25));
    int ball_x = (WIDTH - 25) / 2;
    int ball_y = (HEIGHT - 25) /2;
    int ball_dx = 10;
    int ball_dy = 0;

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
        // move the paddle down with the down key
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (curr_height < 850){
                curr_height += 10;
            }
        }

        window.clear();
        
        // check for ball colliding with right paddle (player paddle)
        // Width of the window -95 because -70 is where the paddle is at and extra -25 for the width of the ball
        if ((ball_x >= WIDTH - 95) && (ball_x <= 1240) && (ball_y > curr_height-25) && (ball_y < curr_height + PADDLE_H)) {
            ball_dx = -15;
            // depending on where the ball hits the paddle decide the y change
            ball_dy = (ball_y + 12.5 - (2 * curr_height + PADDLE_H)/2)/4;
        // check for collision with the left paddle
        // ball_x 60 because of the right edge of the bot paddle met up with ball left edge
        } else if ((ball_x <= 60) && (ball_x >= 35) && (ball_y > bot_height-25) && (ball_y < bot_height + PADDLE_H)) {
            ball_dx = 15;
            ball_dy = (ball_y + 12.5 - (2 * bot_height + PADDLE_H)/2)/4;
        }

        // bouncing off the ceiling and floor
        if ((ball_y <= 0) ||  (ball_y >= HEIGHT - 25)){
            ball_dy = -ball_dy;
        }  


        // when the ball hits the left edge give the point to the player
        if (ball_x <= 0) {
            player_score += 1;
            // move the ball back into the middle
            ball_x = (WIDTH - 25) / 2;
            ball_y = (HEIGHT - 25) /2;
            ball_dx = -5;
            ball_dy = 10;
        // ball hitting the right edge
        } else if (ball_x >= WIDTH - 25) {
            bot_score += 1;
            ball.setPosition((WIDTH - 25) / 2, (HEIGHT - 25) /2);
            ball_x = (WIDTH - 25) / 2;
            ball_y = (HEIGHT - 25) /2;      
            ball_dx = 5;   
            ball_dy = 10;   
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
        player_score_display.setString(to_string(player_score));
        player_score_display.setFont(font);
        player_score_display.setFillColor(sf::Color::White);
        player_score_display.setPosition(725, 25);
        player_score_display.setCharacterSize(75);
        window.draw(player_score_display);

        // draw out paddles
        bot_paddle.setPosition(Vector2f(35, bot_height));
        player_paddle.setPosition(Vector2f(WIDTH - 70, curr_height)); 
        window.draw(player_paddle);
        window.draw(bot_paddle);

        // draw out the lines in the middle of the board
        for (int i = 0; i <= HEIGHT; i += 75) {
            sf::RectangleShape square(Vector2f(25,25));
            square.setFillColor(sf::Color::White);
            square.setPosition((WIDTH - 25) / 2, i);
            window.draw(square);
        }

        // ball movement
        ball_x += ball_dx;
        ball_y += ball_dy;
        ball.setPosition(ball_x, ball_y);
        window.draw(ball);

        // bot movement
        // predict where the ball will be heading to and move the bot paddle based on the prediction
        int predicted = ball_y - (ball_dy / ball_dx) * ball_x;
        if (!(predicted > bot_height && predicted < bot_height + PADDLE_H)) {
            // go up more if needed or down more
            if ((bot_height < predicted) && (bot_height < 850)){
                bot_height += 10;
            } else if ((bot_height > predicted) && (curr_height > 0)) {
                bot_height -= 10;
            }
        }
        window.display();
    }

    return 0;
}
