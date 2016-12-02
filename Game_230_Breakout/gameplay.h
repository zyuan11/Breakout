#pragma once
using namespace std;
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "paddle.h"
#include "brick.h"
#include "ball.h"
#include "life.h"
#include "score.h"
#include "main.h"

class gameplay {
	bool isPlaying;
	bool inProgress;
	int levelCnt;

	//Objects on board
	paddle frontPaddle;
	paddle backPaddle;
	ball ballplay;
	std::vector<brick> brickArr;
	score scoreplay;
	std::vector<life> lifeArr;

	//Texture & Font
	sf::Texture paddleTexture;
	sf::Texture ballTexture;
	sf::Texture powerup_brickTexture;
	sf::Texture brick2HitTexture;
	sf::Texture brick1HitTexture;
	sf::Texture lifeTexture;
	sf::Font myFont;

	//Sounds
	sf::SoundBuffer hitWallSoundBuffer;
	sf::Sound hitWall;
	sf::SoundBuffer hitPaddleSoundBuffer;
	sf::Sound hitPaddle;
	sf::SoundBuffer loseLifeSoundBuffer;
	sf::Sound loseLife;
	sf::SoundBuffer damageBrickSoundBuffer;
	sf::Sound damageBrick;
	sf::SoundBuffer destroyBrickSoundBuffer;
	sf::Sound destroyBrick;
	sf::SoundBuffer gameOverSoundBuffer;
	sf::Sound gameOver;
//Others
	sf::Vector2f lastBrickOffset;
	HITMARK lastHitMark;
	sf::Clock clock;



	
public:

	sf::RenderWindow window;
	sf::VideoMode window_video;

	gameplay(void);
	void play();

	void windowDraw();

	void ballCollision();
	void ballCollisionWithWalls();
	void ballCollisionWithPaddles(sf::Vector2f ballOrigin);
	void frontPaddleHitUpdate();
	void backPaddleHitUpdate();
	void ballCollisionWithBricks(sf::Vector2f ballOrigin);
	bool ballCollisionWithSingleBrick(sf::Vector2f ballOrigin, sf::Vector2f brickPos);

	
	void LifeInit();
	void soundInit();
	void DrawLife();

	void loadBrickTexture();
	void levelUpdate();
	bool CheckLevelDone();
	void LoadBricks();
	void loadBricksLevel1();
	void loadBricksLevel2();
	void AddBrick(char ch);
	void DrawBricks();
	void lastBrickOffsetUpdate();
	
	void paddleMove(float deltaTime);
	void powerup();

	bool lifeUpdate();
	void turnUpdate();
	void EndingPageDraw();
	//void winMsgInit();
	void EndThisGame();
};