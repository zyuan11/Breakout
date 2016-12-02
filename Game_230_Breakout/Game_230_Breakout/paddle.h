#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class paddle {
public:
	sf::RectangleShape myPaddleShape;
	
	void createFrontPaddle();
	void createBackPaddle();
	void paddleMoveLeft(float deltaTime);
	void paddleMoveRight(float deltaTime);
	bool isBeyongWindowLeft(float deltaTime);
	bool isBeyongWindowRight(float deltaTime);
	sf::Vector2f getMyPaddleSize();
	void applyPowerUp();
};