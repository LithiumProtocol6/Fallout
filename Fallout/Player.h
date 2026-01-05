#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class Player
{
	int HP;
	int maxHP;
	sf::Texture texture;
	sf::Sprite* sprite;
	void initSprite();
	void initTexture();
public:
	Player();
	~Player();
	void update();
	void render(sf::RenderTarget& target);
};

