#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
struct Coordinates {
	int x;
	int y;
};
class Object
{
private:
	Coordinates tile;
	Coordinates renderCoordinates;
	int width;
	int length;
	Animation standingAnimation;
	Animation walkingAnimation;
	Coordinates tileWalkingTo;
	Coordinates* path;
	bool isWalking;
public:
	void initAnimation(std::string& _texture, int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame);
	Object(int _x,int _y,int _width,int _length);
	~Object();
	void renderObject(); 
	int getTileX();
	int getTileY();
	void setRenderX(int _x);
	void setRendeY(int _y);
	void setPath(int _x, int _y);
	void setWalking(bool _walking);
	sf::Sprite& getSprite();
};

