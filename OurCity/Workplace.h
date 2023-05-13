#ifndef WORKPLACE_H
#define WORKPLACE_H

#include <vector>

#include "Building.h"
#include "Resident.h"

class Resident;
class Workplace : public Building
{
protected:
	unsigned short capacity;
	
	std::vector<int> workers;

public:
	Workplace(Tile* tile);

	unsigned short getCapacity() const;
	std::vector<int> getWorkers();

	void setCapacity(unsigned short cap);

	bool canWorkHere();
	void addWorker(int id);
	void removeWorker(int id);
	void clearWorkers();
};

#endif
