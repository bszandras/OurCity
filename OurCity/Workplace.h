#ifndef WORKPLACE_H
#define WORKPLACE_H

#include <vector>

#include "Building.h"
#include "Resident.h"

class Workplace : public Building
{
protected:
	unsigned short capacity;
	unsigned short tax;
	std::vector<Resident*> workers;

public:
	Workplace(Tile* tile);

	unsigned short getCapacity() const;
	unsigned short getTax() const;

	bool canWorkHere();
	void setTax(unsigned short tax);
	void addWorker(Resident* r);
};

#endif
