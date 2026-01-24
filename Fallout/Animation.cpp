#include "Animation.h"

void Animation::setAnimation(std::string& _texture, int _rows, int _framesInARow,int _maxFrames, int _waitingTilNextFrame)
{
	texture.loadFromFile(_texture);
	frame = 0;
	maxFrames = _maxFrames;
	framesInARow = _framesInARow;
	int rows = _rows;
	int waiting = 0;
	widthOfFrame = texture.getSize().x / framesInARow;
	heightOfFrame = texture.getSize().y / rows;
}

Animation::Animation(std::string& _texture, int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame)
{
	setAnimation(_texture, _rows,_framesInARow, _maxFrames,_waitingTilNextFrame);
}

sf::Sprite& Animation::getFrame()
{
	sf::Sprite sprite(texture);
	sf::IntRect src({ (frame % framesInARow) * widthOfFrame,(frame / framesInARow) * heightOfFrame }, { widthOfFrame,heightOfFrame });
	sprite.setTextureRect(src);
	return sprite;
}
