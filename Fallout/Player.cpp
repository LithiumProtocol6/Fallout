#include "Player.h"

Player::Player()
{
	name = "Johnny Johnson";
}

Player::~Player()
{
	if(sprite) delete sprite;
}
