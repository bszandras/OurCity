#ifndef ZONE_H
#define ZONE_H

#include <vector>

class Zone
{
private:
	std::vector<int> tiles; // Tile ID-s
	unsigned char type;
	// 0 housing
	// 0 industrial
	// 0 service
public:
	Zone(unsigned char type);
	~Zone();

	bool addTile(int tileID);
	bool removeTile(int tileID);
	bool isTileInZone(int tileID) const;
	std::vector<int> getTiles() const;
};

#endif
