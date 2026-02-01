#include "Item.h"
Item::Item(std::string _name, int _damage, int _range, int _quantity, std::string _texture)
{
	texture.loadFromFile(_texture);
}
Item::Item():damage(0),range(0),quantity(0) {
	name = "Item has no name";
	texture.loadFromFile("Textures/NoTexture.png");
}

void Item::operator=(Item& other) {
	name = other.name;
	damage = other.damage;
	range = other.range;
	quantity = other.quantity;
	texture = other.texture;
}
