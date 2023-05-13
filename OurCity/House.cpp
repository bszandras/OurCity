#include "House.h"

/// <summary>
/// House konstruktor
/// </summary>
/// <param name="tile">A Tile, amire a h�zat rakjuk</param>
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
/// Visszaadja a h�z kapacit�s�t
/// </summary>
/// <returns>A h�z kapacit�sa (h�ny ember �lhet benne)</returns>
unsigned short House::getCapacity()
{
	return capacity;
}

/// <summary>
/// Be�ll�tja a h�z kapacit�s�t
/// </summary>
/// <param name="cap">A h�z �j kapacit�sa (h�ny ember �lhet benne)</param>
void House::setCapacity(unsigned short cap)
{
	capacity = cap;
}

/// <summary>
/// Megadja, hogy a h�zba lehet-e k�lt�zni
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
/// Hozz�adja a megadott lak�t a h�zhoz
/// </summary>
/// <param name="id">A hozz�adand� lakos ID-je</param>
void House::addResident(int id) 
{
	this->residents.push_back(id);

	if (residents.size() == capacity)
	{
		// akkor betelik a h�z, �j sprite
		tile->texId -= 3;
	}
}

/// <summary>
/// Elt�vol�tja a megadott lak�t a h�zb�l
/// </summary>
/// <param name="id">Az elt�vo�tani k�v�nt lakos ID-je</param>
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
		// akkor lejjeb l�p egy szinttel az �p�let
		tile->texId += 3;
	}
}

/// <summary>
/// T�rli a residenteket a h�zb�l
/// </summary>
void House::clearResidents()
{
	residents.clear();
}

/// <summary>
/// Ez csak a dynamic cast miatt kell, nem csin�l semmit
/// </summary>
void House::toString()
{
}

/// <summary>
/// Visszaadja a h�zban lak� lakosok ID-j�t
/// </summary>
/// <returns>A h�znan lak� lakosok ID-jeit tartalmaz� vektor</returns>
std::vector<int> House::getResidents()
{
	return residents;
}
