#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ball {
	float ballAngle;
public:
	sf::CircleShape ballShape;
	float ballSpeed;

	ball(void);
	void ballAngleInit();

	void ballReset();
	void ballSpeedUpdate();
	void ballSpeedReset();

	void ballMove(float factor);

	void ballAngleUpdate_TopWall();
	void ballAngleUpdate_LeftWall();
	void ballAngleUpdate_RightWall();

	void ballAngleUpdate_UpCenterPos();
	void ballAngelUpdate_DownCenterPos();
	void ballAngleUpdate_UpLeftCornerPos();
	void ballAngleUpdate_UpRightCornerPos();
	void ballAngleUpdate_DownLeftCornerPos();
	void ballAngleUpdate_DownRightCornerPos();
	void ballAngleUpdate_UpPos(sf::Vector2f CollisionPos, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	void ballAngleUpdate_DownPos(sf::Vector2f CollisionPos, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	
	bool Collision_UpCenterPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_DownCenterPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_UpLeftCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_UpRightCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_DownLeftCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_DownRightCornerPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_UpPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_UpPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize, sf::Vector2f *CollisionPos);
	bool Collision_DownPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_DownPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize, sf::Vector2f *CollisionPos);
	bool Collision_UpCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_DownCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_LeftCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos);
	bool Collision_RightCorner(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_LeftPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);
	bool Collision_RightPos(sf::Vector2f ballOrigin, sf::Vector2f paddlePos, sf::Vector2f paddleSize);

	bool collideWithTopWall();
	bool collideWithBottomWall();
	bool collideWithLeftWall();
	bool collideWithRightWall();

	//HITSTATUS ballCollisionWithBrick(sf::Vector2f ballOrigin, sf::Vector2f);
	
	sf::Vector2f getOrigin();
};