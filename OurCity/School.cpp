#include "School.h"

/// <summary>
/// Iskola konstruktor
/// </summary>
/// <param name="tile">A Tile, amire az iskol�t �p�tj�k</param>
School::School(Tile* tile) : SpecialBuilding(tile)
{
	capacity = 0;
}

School::~School()
{
}

/// <summary>
/// Be�ll�tja az iskola kapacit�s�t
/// </summary>
/// <param name="capacity">A be�ll�tani k�v�nt kapacit�s</param>
void School::setCapacity(int capacity)
{
	this->capacity = capacity;
}

/// <summary>
/// A param�terben kapott lakosokat be�ll�tja az iskola tanul�inak k�z�
/// </summary>
/// <param name="residents">A lakosok</param>
void School::setResidents(std::vector<Resident*> residents)
{
	this->residents = residents;
}

/// <summary>
/// Hozz�ad egy lakost az iskola tanul�i k�z�
/// </summary>
/// <param name="resident">A hozz�adni k�v�nt lakos</param>
/// <returns>true, ha siker�l hozz�adni, false, ha nem</returns>
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
/// T�r�l egy lakost az iskola tanul�i k�z�l
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
/// Megadja az iskola kapacit�s�t.
/// </summary>
/// <returns>Az iskola kapacit�sa</returns>
int School::getCapacity() const
{
	return capacity;
}

/// <summary>
/// Megadja az iskol�ba j�r� lakosok list�j�t
/// </summary>
/// <returns>Az iskol�ba j�r� lakosok list�ja.</returns>
std::vector<Resident*> School::getResidents() const
{
	return residents;
}
