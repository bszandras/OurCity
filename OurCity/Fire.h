#pragma once
#include "TileRect.h"
class Fire
{
private:
	// itt �g a t�z
	Tile* tile;
	float propagationChance;
	// ezek j�t�k�r�k
	int burnTime;
	int maxBurnTime;

	// TODO
	void Propagate();
public:
	Fire(Tile* tile);
	~Fire();
	void Update(int deltaHours);
	int getBurnTime();
	Tile* getTargetTile();
};