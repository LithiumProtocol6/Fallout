#pragma once
#include "Object.h"
#include "Item.h"
class Entity:public Object
{
private:
	Item* inventory;
	int inventorySize;
	int maxHP;
	int HP;
	int stamina;
	int maxStamina;
	int accuracy;
	bool hasAi;

public:
	Entity(int _x, int _y,int maxHP,int HP,int stamina,int maxStamina,int accuracy,bool hasAi);
	void setInventory(Item* _inventory,int _size);
	~Entity();
};

