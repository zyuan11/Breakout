#include "paddle.h"
#include "main.h"

void paddle::createFrontPaddle() {
	myPaddleShape.setSize(FRONT_PADDLE_SIZE);
	myPaddleShape.setPosition(FRONT_PADDLE_POSITION);
}
void paddle::createBackPaddle() {
	myPaddleShape.setSize(BACK_PADDLE_SIZE);
	myPaddleShape.setPosition(BACK_PADDLE_POSITION);
}

//movement
void paddle::paddleMoveLeft(float deltaTime) {
	if (isBeyongWindowLeft(deltaTime)) {
		myPaddleShape.move(-PADDLE_SPEED * deltaTime, 0);
	}
}
void paddle::paddleMoveRight(float deltaTime) {
	if (isBeyongWindowRight(deltaTime)) {
		myPaddleShape.move(PADDLE_SPEED * deltaTime, 0);
	}
}

//check boundary
bool paddle::isBeyongWindowLeft(float deltaTime) {
	sf::Vector2f paddlePos_curr = myPaddleShape.getPosition();
	if (paddlePos_curr.x - PADDLE_SPEED * deltaTime >= WINDOW_LEFT)
		return true;
	else
		return false;
}
bool paddle::isBeyongWindowRight(float deltaTime) {
	sf::Vector2f paddlePos_curr = myPaddleShape.getPosition();
	sf::Vector2f paddleSize_curr = myPaddleShape.getSize();
	if (paddlePos_curr.x + PADDLE_SPEED * deltaTime <= WINDOW_RIGHT - paddleSize_curr.x)
		return true;
	else
		return false;
}

sf::Vector2f paddle::getMyPaddleSize() {
	return myPaddleShape.getSize();
}

void paddle::applyPowerUp() {
	myPaddleShape.setSize(myPaddleShape.getSize() + PADDLE_POWERUP);
}