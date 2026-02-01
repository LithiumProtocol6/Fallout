#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
class Item
{
private:
	std::string name;
	int damage;
	int range;
	int quantity;
	sf::Texture texture;
public:
	Item(std::string _name, int _damage, int _range, int _quantity, std::string _texture);
	Item();
	void operator=(Item& other);

	//Геттеры
	int getRange() const 
	{ 
		return range; 
	}
	int getDamage() const 
	{ 
		return damage; 
	}
	std::string getName() const 
	{ 
		return name; 
	}
};

