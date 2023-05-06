#include "House.h"

House::House(Tile* tile) : Building(tile)
{
	this->tile = tile;
	buildCost = 0;
	maintenanceCost = 0;
	//this->fireChance = 5;
	tile->fireChance += 5;
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

void House::setCapacity(unsigned short cap)
{
	capacity = cap;
}

unsigned short House::getTax()
{
	return tax;
}

bool House::moveIn()
{
	unsigned int reSize = this->residents.size();
	unsigned short capacity = this->capacity;
	if (reSize < capacity) 
	{
		return true;
	}
	return false;
}

void House::setTax(unsigned short tax)
{
	this->tax = tax;
}

void House::addResident(int id)
{
	this->residents.push_back(id);

	if (residents.size() == capacity)
	{
		// akkor betelik a ház, új sprite
		tile->texId -= 3;
	}
}

void House::removeResident(int id)
{
	bool fullbefore = residents.size() == capacity;
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i] == id)
		{
			residents.erase(residents.begin() + i);
		}
	}

	if (residents.size() < capacity && fullbefore)
	{
		// akkor lejjeb lép egy szinttel az épület
		tile->texId += 3;
	}
}

void House::clearResidents()
{
	residents.clear();
}

void House::toString()
{
}

std::vector<int> House::getResidents()
{
	return residents;
}
