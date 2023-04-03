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

	void addTile(int tileID);
	void removeTile(int tileID);
};

#endif
