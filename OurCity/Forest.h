#ifndef FOREST_H
#define FOREST_H

#include "SpecialBuilding.h"

class Forest : public SpecialBuilding
{
private:
	int age;

public:
	Forest(Tile* tile);
	~Forest();

	void grow();
	void setAge(int a);
	int getAge() const;
};

#endif
