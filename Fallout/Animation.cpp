#include "Animation.h"

void Animation::setAnimation(std::string& _texture, int _rows, int _framesInARow,int _maxFrames, int _waitingTilNextFrame)
{
	if (!texture.loadFromFile(_texture)) {
		std::cout << "Texture " << _texture << " not found" << std::endl;
		texture.loadFromFile("Textures/NoTexture.png");
		frame = 0;
		maxFrames = 0;
		framesInARow = 1;
		rows = 1;
		waitingTilNextFrame = 1;
		waiting = 0;
		widthOfFrame = texture.getSize().x;
		heightOfFrame = texture.getSize().y;
	}
	else {
		frame = 0;
		maxFrames = _maxFrames;
		framesInARow = _framesInARow;
		rows = _rows;
		waitingTilNextFrame = _waitingTilNextFrame;
		waiting = 0;
		widthOfFrame = texture.getSize().x / framesInARow;
		heightOfFrame = texture.getSize().y / rows;
	}
}

Animation::Animation(std::string& _texture, int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame)
{
	setAnimation(_texture, _rows,_framesInARow, _maxFrames,_waitingTilNextFrame);
}

Animation::Animation()
{
	texture.loadFromFile("Textures/NoTexture.png");
	frame = 0;
	maxFrames = 0;
	framesInARow = 1;
	rows = 1;
	waitingTilNextFrame = 1;
	waiting = 0;
	widthOfFrame = texture.getSize().x;
	heightOfFrame = texture.getSize().y;
}

sf::Sprite& Animation::getFrame()
{
	if (waiting == waitingTilNextFrame) {
		frame++;
		waiting = 0;
	}
	sf::Sprite sprite(texture);
	sf::IntRect src({ (frame % framesInARow) * widthOfFrame,(frame / framesInARow) * heightOfFrame }, { widthOfFrame,heightOfFrame });
	sprite.setTextureRect(src);
	sprite.setScale({ (float)widthOfFrame,(float)heightOfFrame });
	waiting++;
	return sprite;
}
