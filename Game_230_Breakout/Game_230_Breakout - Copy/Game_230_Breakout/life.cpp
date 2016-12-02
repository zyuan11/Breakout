#include "life.h"
#include "main.h"

life::life(int id_i, sf::Vector2f lifePos, sf::Texture *brickTexture) {
	myLifeShape.setPosition(lifePos);
	myLifeShape.setRadius(LIFE_RADIUS);
	myLifeShape.setTexture(brickTexture);
	myLifeID = id_i;
}