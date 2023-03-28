#include "House.h"

House::House(Tile* tile) : Building(tile)
{
	buildCost = 0;
	maintenanceCost = 0;

	capacity = 4;
	tax = 0;
}

House::~House()
{
}

int House::getCapacity()
{
	return capacity;
}

int House::getTax()
{
	return tax;
}

void House::setTax(int tax)
{
	this->tax = tax;
}
