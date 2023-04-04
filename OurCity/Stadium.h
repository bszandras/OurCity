#ifndef STADIUM_H
#define STADIUM_H

#include "SpecialBuilding.h"
#include <vector>

class Stadium : public SpecialBuilding
{
private:
	int range;
	std::vector<int> rangeTiles; // TileIDs of tiles in range

public:
	Stadium(Tile* tile);
	~Stadium();

	void setRange(int r);
	void setRangeTiles(std::vector<int> tiles);

	int getRange() const;
	std::vector<int> getRangeTiles() const;
};

#endif
