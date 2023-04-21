#pragma once
#include "TileRect.h"
class Fire
{
private:
	// itt �g a t�z
	Tile* tile;
	float propagationChance;
	// ezek j�t�knapok
	// naponta van es�lye terjedni
	int burnTime;
	int maxBurnTime;
	// ezt olvassa a world �s a world kezeli a terjed�st
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