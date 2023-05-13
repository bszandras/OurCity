#ifndef SCHOOL_H
#define SCHOOL_H

#include "SpecialBuilding.h"
#include "Resident.h"
#include <vector>

class School : public SpecialBuilding
{
protected:
	int capacity;
	std::vector<Resident*> residents;

public:
	School(Tile* tile);
	~School();

	void setCapacity(int capacity);
	void setResidents(std::vector<Resident*> residents);

	bool addResident(Resident* resident);
	bool removeResident(Resident* resident);

	int getCapacity() const;
	std::vector<Resident*> getResidents() const;
};

#endif
