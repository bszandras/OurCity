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
	unsigned short tax;
	std::vector<Resident*> residents;

public:
	House(Tile* tile);
	~House();

	unsigned short getCapacity();
	unsigned short getTax();
	bool moveIn();

	void setTax(unsigned short tax);
	void addResident(Resident* r);

	void toString() override;

	std::vector<Resident*> getResidents();
};

#endif