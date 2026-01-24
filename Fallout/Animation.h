#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
class Animation
{
private:
	int frame;
	int maxFrames;
	int framesInARow;
	int rows;
	sf::Texture texture;
	int waitingTilNextFrame;
	int waiting;
	int widthOfFrame;
	int heightOfFrame;
public:
	void setAnimation(std::string& _texture, int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame);
	Animation(std::string& _texture,int _rows, int _framesInARow, int _maxFrames, int _waitingTilNextFrame);
	sf::Sprite& getFrame();
};

