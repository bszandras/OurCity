#ifndef FIRESTATION_H
#define FIRESTATION_H

#include "SpecialBuilding.h"
#include <vector>

class FireStation : public SpecialBuilding
{
private:
	int range;
	std::vector<int> rangeTiles; // TileIDs of tiles in range
	bool available;

public:
	FireStation(Tile* tile);
	~FireStation();

	void setRange(int r);
	void setRangeTiles(std::vector<int> tiles);
	void setAvailable(bool a);

	int getRange() const;
	std::vector<int> getRangeTiles() const;
	bool isAvailable() const;

};

#endif
