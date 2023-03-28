#ifndef WORKPLACE_H
#define WORKPLACE_H

#include "Building.h"

class Workplace : public Building
{
protected:
	int capacity;
	int tax;

public:
	Workplace(Tile* tile);

	int getCapacity() const;
	int getTax() const;
	void setTax(int tax);
};

#endif
