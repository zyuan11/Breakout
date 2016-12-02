#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//WINDOW
const float WINDOW_WIDTH = 900;
const float WINDOW_HEIGHT = 950;
const float WINDOW_LEFT = 0;
const float WINDOW_RIGHT = 900;
const float WINDOW_TOP = 100;
const float WINDOW_BOTTOM = 950;

//COLOR
const sf::Color BACK_COLOR = sf::Color(222, 230, 249, 255);
const sf::Color PADDLE_COLOR = sf::Color(255, 230, 231, 255);
const sf::Color TEXT_COLOR = sf::Color(255, 230, 231, 255);

//PADDLE
const sf::Vector2f FRONT_PADDLE_SIZE(30, 20);
const sf::Vector2f BACK_PADDLE_SIZE(50, 20);
const sf::Vector2f PADDLE_POWERUP(30, 0);
const sf::Vector2f FRONT_PADDLE_POSITION(420, 700);
const sf::Vector2f BACK_PADDLE_POSITION(415, 900);
const float PADDLE_SPEED = 500;


//BALL
const float BALL_RADIUS = 10;
const sf::Vector2f BALL_INIT_POSITION(425, 680);
const float BALL_MIN_SPEED = 200;
const float BALL_SPEED2 = 300;
const float BALL_SPEED3 = 400;
const float BALL_SPEED4 = 500;
const float BALL_SPEED5 = 600;
const float BALL_MAX_SPEED = 700;
const enum HITMARK {frontPaddleMark = 1, backPaddleMark = 2};

//COLLISION & ANGLE
const sf::Vector2f NO_COLLISION_POSITION(-1, -1);
const int CIRCLE_DEGREE = 360.0;
const int MAX_DEGREE = 70.0;
const float PI = 3.14159265359;
const float PI_2 = 2.0 * PI;
const float PI_3_2 = (3.0 / 2.0) * PI;
const float PI_1_2 = (1.0 / 2.0) * PI;
const float MAX_RADIAN = MAX_DEGREE * PI_2 / CIRCLE_DEGREE;

//BRICK
const enum BRICKCATE { HIT1 = 0, HIT2 = 1, POWERUP = 2 };
const sf::Vector2f BRICK_SIZE(100, 50);
const sf::Vector2f FIRST_BRICK_POSITION(0, 100);

//SCORE
const sf::Vector2f SCORE_TEXT_POSITION(30, 30);
const int SCORE_TEXT_SIZE = 30;
const enum POINTS {hitPoint = 1, backPaddlePoint = 3, frontPaddlePoint = 5};

//LIFE
const float LIFE_RADIUS = 20;
const sf::Vector2f LIFE_POSITION1(600, 30);
const sf::Vector2f LIFE_POSITION2(700, 30);
const sf::Vector2f LIFE_POSITION3(800, 30);

//WIN MESSAGE
const int WINMSG_SIZE = 40;
const sf::Vector2f WINMSG_POSITION(350, 250);