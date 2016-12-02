#pragma once
#include "main.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class brick {
public:
	sf::RectangleShape myBrickShape;
	sf::Vector2f myBrickPos;
	int hit;
	BRICKCATE myBrickCate;

	brick(char ch_i, sf::Vector2f brickPos, sf::Texture *brickTexture);

	bool brickStatusUpdate(sf::Texture *brickTexture);
	void AssignCateAndHit(char ch_i);
	void PrintBrickInfo();
};