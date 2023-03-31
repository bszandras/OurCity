#ifndef ROAD_H
#define ROAD_H

#include "SpecialBuilding.h"

class Road : public SpecialBuilding
{
private:
	static int idxCounter;
	int idx;
	bool deleted;

public:
	Road(Tile* tile);

	int getIdx() const;
	bool isDeleted() const;
	void setDeleted(bool deleted);

};

#endif
