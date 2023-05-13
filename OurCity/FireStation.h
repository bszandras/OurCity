#ifndef FIRESTATION_H
#define FIRESTATION_H

#include "SpecialBuilding.h"
//#include "FireTruck.h"
#include <vector>
//class FireTruck;
class FireStation : public SpecialBuilding
{
private:
	int range;

	std::vector<Tile* > updatedTiles; // updated Tiles

	bool available;
	//FireTruck* truck;

public:
	FireStation(Tile* tile);
	~FireStation();

	void setRange(int range);
	void setAvailable(bool available);

	int getRange() const;
	bool isAvailable() const;
	void HeliStarted();
	void HeliArrived();

	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
};

#endif
