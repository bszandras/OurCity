#ifndef ZONE_H
#define ZONE_H

#include <vector>

class Zone
{
private:
	std::vector<int> tiles; // Tile ID-s
	unsigned char type;
	double taxRate;
	// 0 housing
	// 1 industrial
	// 2 service
public:
	Zone(unsigned char type);
	~Zone();

	bool addTile(int tileID);
	bool removeTile(int tileID);
	bool isTileInZone(int tileID) const;
	std::vector<int> getTiles() const;
	int tileCount();

	double getTaxRate() const;
	void setTaxRate(double taxRate);
};

#endif
