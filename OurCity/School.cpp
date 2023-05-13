#include "School.h"

/// <summary>
/// Iskola konstruktor
/// </summary>
/// <param name="tile">A Tile, amire az iskolát építjük</param>
School::School(Tile* tile) : SpecialBuilding(tile)
{
	capacity = 0;
}

School::~School()
{
}

/// <summary>
/// Beállítja az iskola kapacitását
/// </summary>
/// <param name="capacity">A beállítani kívánt kapacitás</param>
void School::setCapacity(int capacity)
{
	this->capacity = capacity;
}

/// <summary>
/// A paraméterben kapott lakosokat beállítja az iskola tanulóinak közé
/// </summary>
/// <param name="residents">A lakosok</param>
void School::setResidents(std::vector<Resident*> residents)
{
	this->residents = residents;
}

/// <summary>
/// Hozzáad egy lakost az iskola tanulói közé
/// </summary>
/// <param name="resident">A hozzáadni kívánt lakos</param>
/// <returns>true, ha sikerül hozzáadni, false, ha nem</returns>
bool School::addResident(Resident* resident)
{
	for (std::size_t i = 0; i < residents.size(); i++)
	{
		if (residents[i] == resident)
		{
			return false;
		}
	}
	residents.push_back(resident);
	return true;
}

/// <summary>
/// Töröl egy lakost az iskola tanulói közül
/// </summary>
/// <param name="resident">A lakos</param>
/// <returns></returns>
bool School::removeResident(Resident* resident)
{
	for (std::size_t i = 0; i < residents.size(); i++)
	{
		if (residents[i] == resident)
		{
			residents.erase(residents.begin() + i);
			return true;
		}
	}
	return false;
	
}

/// <summary>
/// Megadja az iskola kapacitását.
/// </summary>
/// <returns>Az iskola kapacitása</returns>
int School::getCapacity() const
{
	return capacity;
}

/// <summary>
/// Megadja az iskolába járó lakosok listáját
/// </summary>
/// <returns>Az iskolába járó lakosok listája.</returns>
std::vector<Resident*> School::getResidents() const
{
	return residents;
}
