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
	std::vector<int> rangeTiles; // TileIDs of tiles in range
	std::vector<Tile* > updatedTiles; // updated Tiles
	bool available;
	//FireTruck* truck;

public:
	FireStation(Tile* tile);
	~FireStation();

	void setRange(int r);
	void setRangeTiles(std::vector<int> tiles);
	void setAvailable(bool a);

	int getRange() const;
	std::vector<int> getRangeTiles() const;
	bool isAvailable() const;
	void HeliStarted();
	void HeliArrived();

	void UpdateAreaAfterBuilding(Tile** tiles, int tileCount);
	void UpdateAreaAfterDestruction();
};

#endif
