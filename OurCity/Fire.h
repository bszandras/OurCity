#pragma once
#include "TileRect.h"
class Fire
{
private:
	// itt ég a tûz
	Tile* tile;
	float propagationChance;
	// ezek játéknapok
	// naponta van esélye terjedni
	int burnTime;
	int maxBurnTime;
	// ezt olvassa a world és a world kezeli a terjedést
	bool needsToPropagate = false;
	// TODO
	void Propagate();
public:
	Fire(Tile* tile);
	~Fire();
	void Update(int deltaDays);
	int getBurnTime();
	int getMaxBurnTime();
	Tile* getTargetTile();
	bool shouldPropagate();
};