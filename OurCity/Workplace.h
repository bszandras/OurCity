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
	unsigned short tax;
	//std::vector<Resident*> workers;
	std::vector<int> workers;

public:
	Workplace(Tile* tile);

	unsigned short getCapacity() const;
	void setCapacity(unsigned short cap);
	unsigned short getTax() const;

	bool canWorkHere();
	void setTax(unsigned short tax);
	void addWorker(int id);
	void removeWorker(int id);
	void clearWorkers();
	std::vector<int> getWorkers();
};

#endif
