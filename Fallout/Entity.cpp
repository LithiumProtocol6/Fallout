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
	isAggressive = false;
	equippedWeapon = nullptr;
	visionRange = 10.0f;
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
	isAggressive = false;
	equippedWeapon = nullptr;
	visionRange = 10.0f;
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

bool Entity::isTargetInWeaponRange(Entity& target)
{
	if (!equippedWeapon)
	{
		return false;
	}

	int dx = target.getTileX() - tile.x;
	int dy = target.getTileY() - tile.y;

	float dist = static_cast<float>(sqrt(dx * dx + dy * dy));
	return dist <= equippedWeapon->getRange();
}

void Entity::trimPathToWeaponRange()
{
	if (!equippedWeapon)
	{
		return;
	}

	while (!path.empty())
	{
		auto& last = path.back();
		int dx = last.x - tile.x;
		int dy = last.y - tile.y;
		float dist = static_cast<float>(sqrt(dx * dx + dy * dy));

		if (dist <= equippedWeapon->getRange())
			break;

		path.pop_back();
	}
}

bool Entity::canSeePlayer(Entity& player) const
{
	if (!hasAi || !isAggressive)
	{
		return false;
	}

	int dx = player.getTileX() - tile.x;
	int dy = player.getTileY() - tile.y;
	float dist = sqrt(dx * dx + dy * dy);

	return dist <= visionRange;
}

// Атака цели
void Entity::attack(Entity& target)
{
	if (!hasAi || !equippedWeapon || !target.hasAi)
	{
		return;
	}

	std::cout << "Entity attacks player. Damage: " << equippedWeapon->getDamage() << std::endl;
}

// логика ИИ
void Entity::updateAI(Entity& player)
{
	if (!hasAi || !isAggressive) return;

	setPath(player.getTileX(), player.getTileY());

	if (!canSeePlayer(player))
	{
		isWalking = false;
		return;
	}

	// Обрезаем путь до дистанции оружия
	trimPathToWeaponRange();

	// Если путь ещё есть — идём
	if (!path.empty())
	{
		isWalking = true;
	}
	else
	{
		isWalking = false;
	}

	// Если цель в радиусе оружия — атакуем
	if (isTargetInWeaponRange(player))
	{
		isWalking = false;
		attack(player);
	}
}

// Геттеры/сеттеры
void Entity::setIsAggressive(bool aggressive) 
{ 
	isAggressive = aggressive; 
}
bool Entity::getIsAggressive() const 
{ 
	return isAggressive; 
}
void Entity::setVisionRange(float range) 
{ 
	visionRange = range; 
}

Entity::~Entity()
{
	inventorySize = 0;
	std::cout << "Entity deleted" << std::endl;
}
