#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Player
{
	std::string name;
	int HP;
	int maxHP;
	sf::Texture texture;
	int currentFrame;
	int maxFrames;
	int frameDistance;
	sf::Sprite* sprite;
public:
	Player();
	~Player();
	void initTexture(const char* name);
	void updateAnimationSprite(int frame,int x,int y);
};

