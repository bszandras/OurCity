#ifndef HOUSE_H
#define HOUSE_H

#include "Building.h"

class House : public Building
{
private:
	int capacity;
	int tax;

public:
	House(Tile* tile);
	~House();

	int getCapacity();
	int getTax();

	void setTax(int tax);
};

#endif