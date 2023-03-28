#ifndef HOUSE_H
#define HOUSE_H

#include "Building.h"

class House : public Building
{
private:
	unsigned short capacity;
	unsigned short tax;

public:
	House(Tile* tile);
	~House();

	unsigned short getCapacity();
	unsigned short getTax();

	void setTax(unsigned short tax);
};

#endif