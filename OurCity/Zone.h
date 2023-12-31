#ifndef ZONE_H
#define ZONE_H

#include <vector>
#include "Tile.h"


class Zone
{
private:
	std::vector<int> tiles; // Tile ID-s
	unsigned char type;
	// 0 housing
	// 1 industrial
	// 2 service

	float taxRate;
	
public:
	Zone(unsigned char type);
	~Zone();

	bool addTile(int tileID);
	bool removeTile(int tileID);
	bool isTileInZone(int tileID) const;
	std::vector<int> getTiles() const;
	int tileCount();
	int getType();

	float getTaxRate() const;
	void setTaxRate(float taxRate);
	float* getTaxRateHandle();
};

struct ZoneStatData
{
	Zone* z;
	int tileCount;
	Tile* tiles;
};

#endif
