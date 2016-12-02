#include "ball.h"
#include "main.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

ball::ball(void) {
	ballShape.setPosition(BALL_INIT_POSITION);
	ballShape.setRadius(BALL_RADIUS);
	ballSpeed = BALL_MIN_SPEED;
	ballAngleInit();
}
void ball::ballAngleInit() {
	srand(time(NULL));
	do
	{
		ballAngle = (rand() % CIRCLE_DEGREE * PI_2) / CIRCLE_DEGREE;
	} while (sin(ballAngle) > -0.7f);
}
void ball::ballReset() {
	ballShape.setPosition(BALL_INIT_POSITION);
	ballAngleInit();
}

void ball::ballSpeedUpdate() {
	ballSpeed += 100;
}
void ball::ballSpeedReset() {
	ballSpeed = BALL_MIN_SPEED;
}

void ball::ballMove(float factor) {
	ballShape.move(cos(ballAngle) * factor, sin(ballAngle) * factor);
}

//ball angle updates when collides with walls
void ball::ballAngleUpdate_TopWall() {
	ballAngle = -ballAngle;
}
void ball::ballAngleUpdate_LeftWall() {
	ballAngle = PI - ballAngle;
}
void ball::ballAngleUpdate_RightWall() {
	ballAngle = PI - ballAngle;
}

//ball angle updates with collides with paddle / brick
void ball::ballAngleUpdate_UpCenterPos() {
	ballAngle = PI_3_2;
}
void ball::ballAngelUpdate_DownCenterPos() {
	ballAngle = PI_1_2;
}
void ball::ballAngleUpdate_UpLeftCornerPos() {
	ballAngle = PI_3_2 - MAX_RADIAN;
}
void ball::ballAngleUpdate_UpRightCornerPos() {
	ballAngle = PI_3_2 + MAX_RADIAN;
}
void ball::ballAngleUpdate_DownLeftCornerPos() {
	ballAngle = PI_1_2 + MAX_RADIAN;
}
void ball::ballAngleUpdate_DownRightCornerPos() {
	ballAngle = PI_1_2 - MAX_RADIAN;
}
void ball::ballAngleUpdate_UpPos(sf::Vector2f CollisionPos, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	ballAngle = PI_3_2 - (((float)(paddleSize.x / 2.0 + paddlePos.x - CollisionPos.x) / (float)(paddleSize.x / 2)) * MAX_DEGREE) / CIRCLE_DEGREE * PI_2;
}
void ball::ballAngleUpdate_DownPos(sf::Vector2f CollisionPos, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	ballAngle = PI_1_2 + ((float)(paddleSize.x / 2.0 + paddlePos.x - CollisionPos.x) / (float)(paddleSize.x / 2) * MAX_DEGREE) / CIRCLE_DEGREE * PI_2;
}

//ball collides with walls
bool ball::collideWithTopWall() {
	if (ballShape.getPosition().y <= WINDOW_TOP)
		return true;
	else
		return false;
}
bool ball::collideWithBottomWall() {
	if (ballShape.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT)
		return true;
	else
		return false;
}
bool ball::collideWithLeftWall() {
	if (ballShape.getPosition().x <= 0)
		return true;
	else
		return false;
}
bool ball::collideWithRightWall() {
	if (ballShape.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH)
		return true;
	else
		return false;
}

//ball collides with paddles / bricks
bool ball::Collision_UpCenterPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	if (ballOrigin.x == paddlePos.x + paddleSize.x / 2 &&
		Collision_UpPos(ballOrigin, paddlePos, paddleSize)) {
		return true;
	}
	else
		return false;
	
}
bool ball::Collision_DownCenterPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	if (ballOrigin.x == paddlePos.x + paddleSize.x / 2 &&
		Collision_DownPos(ballOrigin, paddlePos, paddleSize)) {
		return true;
	}
	else
		return false;
	
}
bool ball::Collision_UpLeftCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	if (Collision_UpCorner(ballOrigin, paddlePos, paddleSize) &&
		Collision_LeftCorner(ballOrigin, paddlePos)) {
		return true;
	}
	else
		return false;
	
}
bool ball::Collision_UpRightCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	if (Collision_UpCorner(ballOrigin, paddlePos, paddleSize) &&
		Collision_RightCorner(ballOrigin, paddlePos, paddleSize)) {
		return true;
	}
	else
		return false;
	
}
bool ball::Collision_DownLeftCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	if (Collision_DownCorner(ballOrigin, paddlePos, paddleSize) &&
		Collision_LeftCorner(ballOrigin, paddlePos)) {
		return true;
	}
	else
		return false;
	
}
bool ball::Collision_DownRightCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	if (Collision_DownCorner(ballOrigin, paddlePos, paddleSize) &&
		Collision_RightCorner(ballOrigin, paddlePos, paddleSize)) {
		return true;
	}
	else
		return false;
	
}
bool ball::Collision_UpPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.y + BALL_RADIUS >= paddlePos.y &&
		ballOrigin.y + BALL_RADIUS < paddlePos.y + paddleSize.y / 2);
}
bool ball::Collision_UpPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize, sf::Vector2f *CollisionPos) {
	if (ballOrigin.x > paddlePos.x &&
		ballOrigin.x < paddlePos.x + paddleSize.x &&
		ballOrigin.y + BALL_RADIUS >= paddlePos.y &&
		ballOrigin.y + BALL_RADIUS < paddlePos.y + paddleSize.y / 2) {
		CollisionPos->x = ballOrigin.x;
		CollisionPos->y = ballOrigin.y + BALL_RADIUS;
		return true;
	}
	else
		return false;
}
bool ball::Collision_DownPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.y - BALL_RADIUS >= paddlePos.y + paddleSize.y / 2 &&
		ballOrigin.y - BALL_RADIUS < paddlePos.y + paddleSize.y);
}
bool ball::Collision_DownPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize, sf::Vector2f *CollisionPos) {
	if (ballOrigin.x > paddlePos.x &&
		ballOrigin.x < paddlePos.x + paddleSize.x &&
		ballOrigin.y - BALL_RADIUS >= paddlePos.y + paddleSize.y / 2 &&
		ballOrigin.y - BALL_RADIUS < paddlePos.y + paddleSize.y) {
		CollisionPos->x = ballOrigin.x;
		CollisionPos->y = ballOrigin.y - BALL_RADIUS;
		return true;
	}
	else
		return false;
}
bool ball::Collision_UpCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.y >= paddlePos.y - BALL_RADIUS &&
		ballOrigin.y <= paddlePos.y + paddleSize.y / 2);
}
bool ball::Collision_DownCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.y > paddlePos.y + paddleSize.y / 2 &&
		ballOrigin.y <= paddlePos.y + paddleSize.y + BALL_RADIUS);
}
bool ball::Collision_LeftCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos) {
	return (ballOrigin.x >= paddlePos.x - BALL_RADIUS &&
		ballOrigin.x <= paddlePos.x);
}
bool ball::Collision_RightCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.x >= paddlePos.x + paddleSize.x &&
		ballOrigin.x <= paddlePos.x + paddleSize.x + BALL_RADIUS);
}
bool ball::Collision_LeftPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.x > paddlePos.x &&
		ballOrigin.x < paddlePos.x + paddleSize.x / 2);
}
bool ball::Collision_RightPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize) {
	return (ballOrigin.x > paddlePos.x + paddleSize.x / 2 &&
		ballOrigin. x < paddlePos.x + paddleSize.x);
}



//others
sf::Vector2f ball::getOrigin() {
	sf::Vector2f ballPos_Curr = ballShape.getPosition();
	sf::Vector2f ballOrigin;
	ballOrigin.x = ballPos_Curr.x + BALL_RADIUS;
	ballOrigin.y = ballPos_Curr.y + BALL_RADIUS;
	return ballOrigin;
}

