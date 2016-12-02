#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class life {
	int myLifeID;
public:
	sf::CircleShape myLifeShape;
	life(int id_i, sf::Vector2f lifePos, sf::Texture *brickTexture);
};