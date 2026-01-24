#pragma once
#include "Object.h"
#include "Item.h"
class Entity:public Object
{
private:
	Item* Inventory;
	int maxHP;
	int HP;
	int stamina;
	int maxStamina;
	int accuracy;
public:
	
};

