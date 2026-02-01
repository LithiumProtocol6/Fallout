#include "Entity.h"

Entity::Entity(int _x, int _y, int _maxHP, int _HP, int _stamina, int _maxStamina, int _accuracy, bool _hasAi) :Object(_x, _y)
{
	maxHP = _maxHP;
	HP = _HP;
	stamina = _stamina;
	maxStamina = _maxStamina;
	accuracy = _accuracy;
	hasAi = _hasAi;
	inventorySize = 0;
}

Entity::Entity()
{
	maxHP = 0;
	HP = 0;
	stamina = 0;
	maxStamina = 0;
	accuracy = 0;
	hasAi = 0;
	inventorySize = 0;
}

void Entity::setEntity(int _x, int _y, int _maxHP, int _HP, int _stamina, int _maxStamina, int _accuracy, bool _hasAi)
{
	tile.x = _x;
	tile.y = _y;
	maxHP = _maxHP;
	HP = _HP;
	stamina = _stamina;
	maxStamina = _maxStamina;
	accuracy = _accuracy;
	hasAi = _hasAi;
}

void Entity::setInventory(std::vector<Item> _inventory, int _size)
{
	if (_inventory.empty() || _size <= 0) return;
	if (inventorySize > 0) inventory.clear();
	inventorySize = _size;
	inventory.resize(inventorySize);
	inventory = _inventory;
}

void Entity::operator=(const Entity& other)
{
	maxHP = other.maxHP;
	HP = other.HP;
	stamina = other.stamina;
	maxStamina = other.maxStamina;
	accuracy = other.accuracy;
	hasAi = other.hasAi;
	inventorySize = other.inventorySize;
	setInventory(other.inventory, inventorySize);
}

bool Entity::hasInventory()
{
	return inventorySize>0;
}

Entity::~Entity()
{
	inventorySize = 0;
	std::cout << "Entity deleted" << std::endl;
}
