#ifndef POLICESTATION_H
#define POLICESTATION_H

#include "SpecialBuilding.h"
#include <vector>

class PoliceStation : public SpecialBuilding
{
private:
	int range;

	std::vector<Tile*> updatedTiles; // Tiles that have been updated	

public:
	PoliceStation(Tile* tile);
	~PoliceStation();

	int getRange() const;

	void setRange(int range);
	
	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
	
};

#endif
