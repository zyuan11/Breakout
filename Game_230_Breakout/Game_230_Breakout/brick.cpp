#include "brick.h"
#include <iostream>
using namespace std;

brick::brick(char ch_i, sf::Vector2f brickPos, sf::Texture *brickTexture) {
	AssignCateAndHit(ch_i);
	myBrickShape.setSize(BRICK_SIZE);
	myBrickShape.setPosition(brickPos);
	myBrickShape.setTexture(brickTexture);
	myBrickPos = brickPos;
}

void brick::AssignCateAndHit(char ch_i) {
	switch (ch_i) {
	case '1':
		myBrickCate = HIT1;
		hit = 1;
		break;
	case '2':
		myBrickCate = HIT2;
		hit = 2;
		break;
	case '3':
		myBrickCate = POWERUP;
		hit = 1;
		break;
	default:
		break;
	}
}

//true if this brick is dead, false if not
bool brick::brickStatusUpdate(sf::Texture *brickTexture) {
	//update hits
	hit--;
	//check hits left
	if (hit == 0)
		return true;
	else {
		myBrickShape.setTexture(brickTexture);
		return false;
	}
}


void brick::PrintBrickInfo() {
	cout << "my position(" << myBrickShape.getPosition().x << ", " << myBrickShape.getPosition().y << ")" << endl;
}