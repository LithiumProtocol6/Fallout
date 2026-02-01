#include "Object.h"

void Object::initAnimation(std::string& _texture, int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame, int animNum)
{
	if (animNum == 1) standingAnimation.setAnimation(_texture, _rows, _framesInARow, _maxFrames, _waitingTilNextFrame);
	else if (animNum == 2)standingAnimation.setAnimation(_texture, _rows, _framesInARow, _maxFrames, _waitingTilNextFrame);
}
Object::Object(int _x, int _y)
{
	tile.x = _x;
	tile.y = _y;
    isWalking = 0;
    int pathSize = 0;
    walkingOffsetX = 0;
    walkingOffsetY = 0;
    walkingSpeed = 0;
}

Object::Object()
{
    tile.x = 0;
    tile.y = 0;
    isWalking = 0;
    int pathSize = 0;
    walkingOffsetX = 0;
    walkingOffsetY = 0;
    walkingSpeed = 0;
}

Object::~Object()
{
}

int Object::getTileX()
{
	return tile.x;
}

int Object::getTileY()
{
	return tile.y;
}

void Object::setRenderX(int _x)
{
	renderCoordinates.x = _x;
}

void Object::setRenderY(int _y)
{
	renderCoordinates.y = _y;
}

void Object::setPath(int _x, int _y)
{
    int dx = std::abs(_x - tile.x);
    int dy = std::abs(_y - tile.x);
    int sx = (tile.x < _x) ? 1 : -1;
    int sy = (tile.y < _y) ? 1 : -1;
    int size = dx + dy + 1;
    int cx = tile.x;
    int cy = tile.y;
    int err = dx - dy;
    int i = 0;
    if (!path.empty()) path.clear();
    path.resize(size);
    path[i].x = cx;
    path[i].y = cy;
    ++i;
    while (cx != _x || cy != _y) {
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            cx += sx;
        }
        else if (e2 < dx) {
            err += dx;
            cy += sy;
        }
        else {
            err -= dy;
            cx += sx;
        }
        Coordinates c = { cx,cy };
        path.emplace_back(c);
        ++i;
    }
    size = i;
}

void Object::setWalking(bool _walking)
{
	isWalking = _walking;
}

bool Object::getWalking()
{
	return isWalking;
}

sf::Sprite& Object::getSprite()
{
	if (isWalking) return walkingAnimation.getFrame();
	else return standingAnimation.getFrame();
}

void Object::setWalkingOffsetX(int _walkingOffsetX)
{
    walkingOffsetX = _walkingOffsetX;
}

void Object::setWalkingOffsetY(int _walkingOffsetY)
{
    walkingOffsetY = _walkingOffsetY;
}

void Object::setWalkingSpeed(int _walkingSpeed)
{
    walkingSpeed = _walkingSpeed;
}

int Object::getWalkingOffsetX()
{
    return walkingOffsetX;
}

int Object::getWalkingOffsetY()
{
    return walkingOffsetY;
}

int Object::getWalkingSpeed()
{
    return walkingSpeed;
}
