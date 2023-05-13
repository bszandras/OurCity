#include "House.h"

/// <summary>
/// House konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a házat rakjuk</param>
House::House(Tile* tile) : Building(tile)
{
	this->tile = tile;
	buildCost = 0;
	maintenanceCost = 0;
	tile->fireChance += 5;
	capacity = 4;
}

House::~House()
{
}

/// <summary>
/// Visszaadja a ház kapacitását
/// </summary>
/// <returns>A ház kapacitása (hány ember élhet benne)</returns>
unsigned short House::getCapacity()
{
	return capacity;
}

/// <summary>
/// Beállítja a ház kapacitását
/// </summary>
/// <param name="cap">A ház új kapacitása (hány ember élhet benne)</param>
void House::setCapacity(unsigned short cap)
{
	capacity = cap;
}

/// <summary>
/// Megadja, hogy a házba lehet-e költözni
/// </summary>
/// <returns>true, ha lehet, false, ha nem</returns>
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

/// <summary>
/// Hozzáadja a megadott lakót a házhoz
/// </summary>
/// <param name="id">A hozzáadandó lakos ID-je</param>
void House::addResident(int id) 
{
	this->residents.push_back(id);

	if (residents.size() == capacity)
	{
		// akkor betelik a ház, új sprite
		tile->texId -= 3;
	}
}

/// <summary>
/// Eltávolítja a megadott lakót a házból
/// </summary>
/// <param name="id">Az eltávoítani kívánt lakos ID-je</param>
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

/// <summary>
/// Törli a residenteket a házból
/// </summary>
void House::clearResidents()
{
	residents.clear();
}

/// <summary>
/// Ez csak a dynamic cast miatt kell, nem csinál semmit
/// </summary>
void House::toString()
{
}

/// <summary>
/// Visszaadja a házban lakó lakosok ID-jét
/// </summary>
/// <returns>A háznan lakó lakosok ID-jeit tartalmazó vektor</returns>
std::vector<int> House::getResidents()
{
	return residents;
}
