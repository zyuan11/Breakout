#include "score.h"
#include "main.h"
#include <iostream>
using namespace std;
#include <String>


score::score(void) {
	myScore = 0;
	myScoreStr = "SCORE: " + to_string(myScore);
	myScoreFont.loadFromFile("arial.ttf");
	myScoreText.setString(myScoreStr);
	myScoreText.setPosition(SCORE_TEXT_POSITION);
	myScoreText.setColor(sf::Color::Black);
	myScoreText.setCharacterSize(SCORE_TEXT_SIZE);
}

void score::scoreUpdate(POINTS newPoint) {
	switch (newPoint) {
	case hitPoint:
		myScore += 1;
		break;
	case backPaddlePoint:
		myScore += 3;
		break;
	case frontPaddlePoint:
		myScore += 5;
		break;
	default:
		break;
	}
	myScoreStr = "SCORE: " + to_string(myScore);
	myScoreText.setString(myScoreStr);

}