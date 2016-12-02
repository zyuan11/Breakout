#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
#include <String>
#include "main.h"

class score {
	int myScore;
	string myScoreStr;
public:
	sf::Text myScoreText;
	sf::Font myScoreFont;
	score();
	void scoreUpdate(POINTS newPoint);
};