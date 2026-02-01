#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
struct Coordinates {
	int x;
	int y;
};
class Object
{
protected:
	Coordinates tile;
	Coordinates renderCoordinates;
	Animation standingAnimation;
	Animation walkingAnimation;
	Coordinates tileWalkingTo;
	std::vector<Coordinates> path;
	int pathSize;
	bool isWalking;
	int walkingOffsetX;
	int walkingOffsetY;
	int walkingSpeed;
public:
	void initAnimation(std::string& _texture, int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame,int animNum);
	Object(int _x,int _y);
	Object();
	~Object();
	int getTileX();
	int getTileY();
	void setRenderX(int _x);
	void setRenderY(int _y);
	void setPath(int _x, int _y);
	void setWalking(bool _walking);
	bool getWalking();
	sf::Sprite& getSprite();
	void setWalkingOffsetX(int _walkingOffsetX);
	void setWalkingOffsetY(int _walkingOffsetY);
	void setWalkingSpeed(int _walkingSpeed);
	int getWalkingOffsetX();
	int getWalkingOffsetY();
	int getWalkingSpeed();

};

