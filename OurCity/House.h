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
	//std::vector<Resident*> residents;
	std::vector<int> residents;

public:
	House(Tile* tile);
	~House();

	unsigned short getCapacity();
	void setCapacity(unsigned short cap);
	unsigned short getTax();
	bool moveIn();

	void setTax(unsigned short tax);
	void addResident(int id);

	void toString() override;

	std::vector<int> getResidents();
};

#endif