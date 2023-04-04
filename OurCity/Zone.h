#ifndef ZONE_H
#define ZONE_H

#include <vector>

class Zone
{
private:
	std::vector<int> tiles; // Tile ID-s
	unsigned char type;

public:
	Zone(unsigned char type);
	~Zone();

	bool addTile(int tileID);
	bool removeTile(int tileID);
	bool isTileInZone(int tileID) const;
	void getTiles(std::vector<int> &tiles);
};

#endif
