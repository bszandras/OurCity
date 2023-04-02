#include "House.h"

House::House(Tile* tile) : Building(tile)
{
	this->tile = tile;
	buildCost = 0;
	maintenanceCost = 0;

	capacity = 4;
	tax = 0;
}

House::~House()
{
}

unsigned short House::getCapacity()
{
	return capacity;
}

unsigned short House::getTax()
{
	return tax;
}

void House::setTax(unsigned short tax)
{
	this->tax = tax;
}
