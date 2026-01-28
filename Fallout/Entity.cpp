#include "Entity.h"

Entity::Entity(int _x, int _y, int _maxHP, int _HP, int _stamina, int _maxStamina, int _accuracy, bool _hasAi):Object(_x, _y)
{
	maxHP = _maxHP;
	HP = _HP;
	stamina = _stamina;
	maxStamina = _maxStamina;
	accuracy = _accuracy;
	hasAi = _hasAi;
}

void Entity::setInventory(Item* _inventory, int _size)
{
	if (inventory) delete[] inventory;
	if (!_inventory) return;
	inventorySize = _size;
	inventory = new Item[inventorySize];
	for (int i = 0; i < inventorySize; i++) {
		inventory[i] = _inventory[i];
	}
}

Entity::~Entity()
{
	if (inventory) delete[] inventory;
}
