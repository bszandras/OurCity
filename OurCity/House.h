#ifndef HOUSE_H
#define HOUSE_H

#include <vector>

#include "Building.h"
#include "Resident.h"

class Resident;

class House : public Building
{
private:
	unsigned short capacity;
	std::vector<int> residents;

public:
	House(Tile* tile);
	~House();

	unsigned short getCapacity();
	std::vector<int> getResidents();

	void setCapacity(unsigned short cap);

	bool moveIn();
	void addResident(int id);
	void removeResident(int id);
	void clearResidents();

	void toString() override;
};

#endif