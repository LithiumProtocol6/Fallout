#include "Item.h"
Item::Item(std::string _name, int _damage, int _range, int _quantity, std::string _texture)
{
	texture.loadFromFile(_texture);
}
Item::Item():damage(0),range(0),quantity(0) {
	name = "Item has no name";
	texture.loadFromFile("Textures/NoTextureItem.png");
}
