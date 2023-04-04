#include "School.h"

School::School(Tile* tile) : SpecialBuilding(tile)
{
	capacity = 0;
}

School::~School()
{
}

void School::setCapacity(int c)
{
	this->capacity = c;
}

void School::setResidents(std::vector<Resident*> residents)
{
	this->residents = residents;
}

bool School::addResident(Resident* resident)
{
	for (size_t i = 0; i < residents.size(); i++)
	{
		if (residents[i] == resident)
		{
			return false;
		}
	}
	residents.push_back(resident);
	return true;
}

bool School::removeResident(Resident* resident)
{
	for (size_t i = 0; i < residents.size(); i++)
	{
		if (residents[i] == resident)
		{
			residents.erase(residents.begin() + i);
			return true;
		}
	}
	return false;
	
}

int School::getCapacity() const
{
	return capacity;
}

std::vector<Resident*> School::getResidents() const
{
	return residents;
}
