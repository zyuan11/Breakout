#include "gameplay.h"

gameplay::gameplay(void) {
	window_video.width = WINDOW_WIDTH;
	window_video.height = WINDOW_HEIGHT;
	window.create(window_video, "Breakout!");

	//paddle
	paddleTexture.loadFromFile("paddle.png");
	frontPaddle.createFrontPaddle();
	frontPaddle.myPaddleShape.setTexture(&paddleTexture);
	backPaddle.createBackPaddle();
	backPaddle.myPaddleShape.setTexture(&paddleTexture);
	
	//ball
	ballTexture.loadFromFile("ball.png");
	ballplay.ballShape.setTexture(&ballTexture);

	//brick
	levelCnt = 2;
	loadBrickTexture();
	lastBrickOffset = FIRST_BRICK_POSITION;
	LoadBricks();

	//score
	scoreplay = score();
	scoreplay.myScoreFont.loadFromFile("arial.ttf");
	scoreplay.myScoreText.setFont(scoreplay.myScoreFont);

	//life
	LifeInit();

	//sound
	soundInit();
	
	isPlaying = true;
	inProgress = false;
}

void gameplay::play() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(BACK_COLOR);

		if (isPlaying) {
			float deltaTime = clock.restart().asSeconds();
			float factor = ballplay.ballSpeed * deltaTime;

			turnUpdate();
			windowDraw();
			ballCollision();

			//movement
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || inProgress)
				inProgress = true;

			if (inProgress) {
				paddleMove(deltaTime);
				ballplay.ballMove(factor);
			}
			
		}
		EndingPageDraw();
		window.display();		
	}
	
}

//ball
void gameplay::ballCollision() {
	sf::Vector2f ballOrigin = ballplay.getOrigin();
	
	//collision with walls
	ballCollisionWithWalls();

	//collision with front and back paddle
	ballCollisionWithPaddles(ballOrigin);

	//collision with bricks
	ballCollisionWithBricks(ballOrigin);
}
void gameplay::ballCollisionWithWalls() {
	if (ballplay.collideWithTopWall()) {
		ballplay.ballAngleUpdate_TopWall();
		hitWall.play();
	}
	else if (ballplay.collideWithLeftWall()) {
		ballplay.ballAngleUpdate_LeftWall();
		hitWall.play();
	}
	else if (ballplay.collideWithRightWall()) {
		ballplay.ballAngleUpdate_RightWall();
		hitWall.play();
	}
	else if (ballplay.collideWithBottomWall()) {
		if (!lifeUpdate())
			EndThisGame();
	}
}
void gameplay::ballCollisionWithPaddles(sf::Vector2f ballOrigin) {
	sf::Vector2f frontPaddlePos = frontPaddle.myPaddleShape.getPosition();
	sf::Vector2f frontPaddleSize = frontPaddle.myPaddleShape.getSize();// getMyPaddleSize();
	sf::Vector2f backPaddlePos = backPaddle.myPaddleShape.getPosition();
	sf::Vector2f backPaddleSize = backPaddle.myPaddleShape.getSize();// getMyPaddleSize();
	sf::Vector2f CollisionPos = NO_COLLISION_POSITION;

	//ball collides with front paddle @ up center position
	if (ballplay.Collision_UpCenterPos(ballOrigin, frontPaddlePos, frontPaddleSize)) {
		ballplay.ballAngleUpdate_UpCenterPos();
		frontPaddleHitUpdate();
	} 

	//ball collides with back paddle @ up center position
	else if (ballplay.Collision_UpCenterPos(ballOrigin, backPaddlePos, backPaddleSize)) {
		ballplay.ballAngleUpdate_UpCenterPos();
		backPaddleHitUpdate();
	}
		
	//ball collides with front paddle @ down center position
	else if (ballplay.Collision_DownCenterPos(ballOrigin, frontPaddlePos, frontPaddleSize)) {
		ballplay.ballAngelUpdate_DownCenterPos();
		frontPaddleHitUpdate();
	}
	
	//ball collides with front paddle @ up left corner position
	else if (ballplay.Collision_UpLeftCornerPos(ballOrigin, frontPaddlePos, frontPaddleSize)) {
		ballplay.ballAngleUpdate_UpLeftCornerPos();
		frontPaddleHitUpdate();
	}
	
	//ball collides with back paddle @ up left corner position
	else if (ballplay.Collision_UpLeftCornerPos(ballOrigin, backPaddlePos, backPaddleSize)) {
		ballplay.ballAngleUpdate_UpLeftCornerPos();
		backPaddleHitUpdate();
	}
		
	//ball collides with front paddle @ up right corner position
	else if (ballplay.Collision_UpRightCornerPos(ballOrigin, frontPaddlePos, frontPaddleSize)) {
		ballplay.ballAngleUpdate_UpRightCornerPos();
		frontPaddleHitUpdate();
	}
	
	//ball collides with back paddle @ up right corner position
	else if (ballplay.Collision_UpRightCornerPos(ballOrigin, backPaddlePos, backPaddleSize)) {
		ballplay.ballAngleUpdate_UpRightCornerPos();
		backPaddleHitUpdate();
	}
		
	//ball collides with front paddle @ down left corner position
	else if (ballplay.Collision_DownLeftCornerPos(ballOrigin, frontPaddlePos, frontPaddleSize)) {
		ballplay.ballAngleUpdate_DownLeftCornerPos();
		frontPaddleHitUpdate();
	}
	
	//ball collides with front paddle @ down right corner position
	else if (ballplay.Collision_DownRightCornerPos(ballOrigin, frontPaddlePos, frontPaddleSize)) {
		ballplay.ballAngleUpdate_DownRightCornerPos();
		frontPaddleHitUpdate();
	}
	
	//ball collides with front paddle @ up left / right position
	else if (ballplay.Collision_UpPos(ballOrigin, frontPaddlePos, frontPaddleSize, &CollisionPos)) {
		ballplay.ballAngleUpdate_UpPos(CollisionPos, frontPaddlePos, frontPaddleSize);
		frontPaddleHitUpdate();
	}
	//ball collides with back paddle @ up left / right position
	else if (ballplay.Collision_UpPos(ballOrigin, backPaddlePos, backPaddleSize, &CollisionPos)) {
		ballplay.ballAngleUpdate_UpPos(CollisionPos, backPaddlePos, backPaddleSize);
		backPaddleHitUpdate();
	}
	
	//ball collides with front paddle @ down left / right position
	else if (ballplay.Collision_DownPos(ballOrigin, frontPaddlePos, frontPaddleSize, &CollisionPos)) {
		ballplay.ballAngleUpdate_DownPos(CollisionPos, frontPaddlePos, frontPaddleSize);
		frontPaddleHitUpdate();
	}
}
void gameplay::frontPaddleHitUpdate() {
	lastHitMark = frontPaddleMark;
	//scoreplay.scoreUpdate(frontPaddlePoint);
}
void gameplay::backPaddleHitUpdate() {
	lastHitMark = backPaddleMark;
	//scoreplay.scoreUpdate(backPaddlePoint);
}
void gameplay::ballCollisionWithBricks(sf::Vector2f ballOrigin) {
	for (int ind = 0; ind < brickArr.size(); ind++) {
		sf::Vector2f brickPos = brickArr[ind].myBrickShape.getPosition();
		
		if (ballCollisionWithSingleBrick(ballOrigin, brickPos)) {
			scoreplay.scoreUpdate(hitPoint);
			cout << "current speed: " << ballplay.ballSpeed << endl;

			if (brickArr[ind].myBrickCate == POWERUP) {
				powerup();
			}

			if (brickArr[ind].brickStatusUpdate(&brick1HitTexture))
				brickArr.erase(brickArr.begin() + ind);

			cout << "brickArr size: " << brickArr.size() << endl;
		}
	}
}
bool gameplay::ballCollisionWithSingleBrick(sf::Vector2f ballOrigin, sf::Vector2f brickPos) {
	sf::Vector2f CollisionPos = NO_COLLISION_POSITION;

	//ball collides with brick @ up center position
	if (ballplay.Collision_UpCenterPos(ballOrigin, brickPos, BRICK_SIZE))
		ballplay.ballAngleUpdate_UpCenterPos();

	//ball collides with brick @ down center position
	else if (ballplay.Collision_DownCenterPos(ballOrigin, brickPos, BRICK_SIZE))
		ballplay.ballAngelUpdate_DownCenterPos();

	//ball collides with brick @ up left corner position
	else if (ballplay.Collision_UpLeftCornerPos(ballOrigin, brickPos, BRICK_SIZE))
		ballplay.ballAngleUpdate_UpLeftCornerPos();

	//ball collides with brick @ up right corner position
	else if (ballplay.Collision_UpRightCornerPos(ballOrigin, brickPos, BRICK_SIZE))
		ballplay.ballAngleUpdate_UpRightCornerPos();

	//ball collides with brick @ down left corner position
	else if (ballplay.Collision_DownLeftCornerPos(ballOrigin, brickPos, BRICK_SIZE))
		ballplay.ballAngleUpdate_DownLeftCornerPos();

	//ball collides with brick @ down right corner position
	else if (ballplay.Collision_DownRightCornerPos(ballOrigin, brickPos, BRICK_SIZE))
		ballplay.ballAngleUpdate_DownRightCornerPos();

	//ball collides with brick @ up left / right position
	else if (ballplay.Collision_UpPos(ballOrigin, brickPos, BRICK_SIZE, &CollisionPos)) {
		ballplay.ballAngleUpdate_UpPos(CollisionPos, brickPos, BRICK_SIZE);
	}

	//ball collides with brick @ up left / right position
	else if (ballplay.Collision_UpPos(ballOrigin, brickPos, BRICK_SIZE, &CollisionPos)) {
		ballplay.ballAngleUpdate_UpPos(CollisionPos, brickPos, BRICK_SIZE);
	}

	//ball collides with brick @ down left / right position
	else if (ballplay.Collision_DownPos(ballOrigin, brickPos, BRICK_SIZE, &CollisionPos))
		ballplay.ballAngleUpdate_DownPos(CollisionPos, brickPos, BRICK_SIZE);

	else
		return false;

	return true;
}

//Sound
void gameplay::soundInit() {
	if (!hitWallSoundBuffer.loadFromFile("hitWall.wav"))
		return;
	hitWall.setBuffer(hitWallSoundBuffer);
	hitWall.setVolume(50);
}

//score
void gameplay::LifeInit() {
	lifeTexture.loadFromFile("ball.png");
	//lifeArr.push_back(life(3, LIFE_POSITION3, &lifeTexture));
	lifeArr.push_back(life(2, LIFE_POSITION2, &lifeTexture));
	lifeArr.push_back(life(1, LIFE_POSITION1, &lifeTexture));
}
void gameplay::DrawLife() {
	for (life i : lifeArr) {
		window.draw(i.myLifeShape);
	}
}

//brick
void gameplay::loadBrickTexture() {
	powerup_brickTexture.loadFromFile("powerup_brick.png");
	brick2HitTexture.loadFromFile("hit2_brick.png");
	brick1HitTexture.loadFromFile("hit1_brick.png");
}
void gameplay::levelUpdate() {
	if (levelCnt == 1)
		levelCnt = 2;
	else if (levelCnt = 2)
		levelCnt = 1;
	LoadBricks();
}
bool gameplay::CheckLevelDone() {
	return (brickArr.size() == 0);
}
void gameplay::LoadBricks() {
	if (levelCnt == 1)
		loadBricksLevel1();
	else if (levelCnt == 2)
		loadBricksLevel2();
}
void gameplay::loadBricksLevel1() {
	char ch;
	fstream fin("level1.txt", fstream::in);
	
	while (fin >> noskipws >> ch) {
		AddBrick(ch);
	}
}
void gameplay::loadBricksLevel2() {
	char ch;
	fstream fin("level2.txt", fstream::in);

	while (fin >> noskipws >> ch) {
		AddBrick(ch);
	}
}
void gameplay::AddBrick(char ch) {
	switch (ch) {
	case '0':
		break;
	case '1':
		brickArr.push_back(brick(ch, lastBrickOffset, &brick1HitTexture));
		break;
	case '2':
		brickArr.push_back(brick(ch, lastBrickOffset, &brick2HitTexture));
		break;
	case '3':
		brickArr.push_back(brick(ch, lastBrickOffset, &powerup_brickTexture));
		break;
	default:
		break;
	}
	lastBrickOffsetUpdate();
}
void gameplay::DrawBricks() {
	for (brick i : brickArr) {
		window.draw(i.myBrickShape);
	}
}
void gameplay::lastBrickOffsetUpdate() {
	if (lastBrickOffset.x < WINDOW_WIDTH - BRICK_SIZE.x) {
		lastBrickOffset.x += BRICK_SIZE.x;
	}
	else {
		lastBrickOffset.y += BRICK_SIZE.y;
		lastBrickOffset.x = 0;
	}
}

//paddle
void gameplay::paddleMove(float deltaTime) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		frontPaddle.paddleMoveLeft(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		frontPaddle.paddleMoveRight(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		backPaddle.paddleMoveLeft(deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		backPaddle.paddleMoveRight(deltaTime);
	}
}
void gameplay::powerup() {
	switch (lastHitMark) {
	case frontPaddleMark:
		frontPaddle.applyPowerUp();
		break;
	case backPaddleMark:
		backPaddle.applyPowerUp(); 
		break;
	default:
		break;
	}
}


//Update life counters, true if there are still lives left, false if not
bool gameplay::lifeUpdate() {
	lifeArr.pop_back();
	if (!lifeArr.empty()) {
		ballplay.ballReset();
		return true;
	}
	else {
		return false;
	}
}

//others
void gameplay::windowDraw() {
	window.draw(frontPaddle.myPaddleShape);
	window.draw(backPaddle.myPaddleShape);
	window.draw(ballplay.ballShape);
	window.draw(scoreplay.myScoreText);
	DrawLife();
	DrawBricks();
}
void gameplay::EndingPageDraw() {
	window.draw(winMsg);
	window.draw(scoreplay.myScoreText);
}
void gameplay::turnUpdate() {
	if (CheckLevelDone()) {
		ballplay.ballReset();
		ballplay.ballSpeedUpdate();
		inProgress = false;
		lastBrickOffset = FIRST_BRICK_POSITION;
		levelUpdate();
	}

}
void gameplay::winMsgInit() {
	winMsg.setString("Game Over");
	winMsg.setFont(myFont);
	winMsg.setCharacterSize(WINMSG_SIZE);
	winMsg.setPosition(WINMSG_POSITION);

}
void gameplay::EndThisGame() {
	isPlaying = false;
}
