#pragma once
#include "Object.h"
#include "Item.h"
class Entity:public Object
{
private:
	std::vector<Item> inventory;
	int inventorySize;
	int maxHP;
	int HP;
	int stamina;
	int maxStamina;
	int accuracy;
	bool hasAi;

public:
	Entity(int _x, int _y,int _maxHP,int _HP,int _stamina,int _maxStamina,int _accuracy,bool _hasAi);
	Entity();
	void setEntity(int _x, int _y, int _maxHP, int _HP, int _stamina, int _maxStamina, int _accuracy, bool _hasAi);
	void setInventory(std::vector<Item> _inventory,int _size);
	void operator=(const Entity& other);
	bool hasInventory();
	~Entity();
};

