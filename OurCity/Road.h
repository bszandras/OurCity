#ifndef ROAD_H
#define ROAD_H

#include "SpecialBuilding.h"


class Road : public SpecialBuilding
{
private:
	static int idCount;
	int id;
public:
	Road(Tile* tile);
	~Road();
	Road(Road& t);

	void setId(int id);

	int getId() const;

};

#endif