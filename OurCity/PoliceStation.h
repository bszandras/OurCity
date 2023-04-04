#ifndef POLICESTATION_H
#define POLICESTATION_H

#include "SpecialBuilding.h"
#include <vector>

class PoliceStation : public SpecialBuilding
{
private:
	int range;
	std::vector<int> rangeTiles; // TileIDs of tiles in range

public:
	PoliceStation(Tile* tile);
	~PoliceStation();

	void setRange(int r);
	void setRangeTiles(std::vector<int> tiles);

	int getRange() const;
	std::vector<int> getRangeTiles() const;
};

#endif
