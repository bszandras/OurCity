#ifndef WORKPLACE_H
#define WORKPLACE_H

#include "Building.h"

class Workplace : public Building
{
protected:
	unsigned short capacity;
	unsigned short tax;

public:
	Workplace(Tile* tile);

	unsigned short getCapacity() const;
	unsigned short getTax() const;
	void setTax(unsigned short tax);
};

#endif
