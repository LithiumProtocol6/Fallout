#include "Player.h"

Player::Player()
{
	if(!texture.loadFromFile("player.png"))
	sprite= new sf::Sprite(texture);
}

Player::~Player()
{
	delete sprite;
}
