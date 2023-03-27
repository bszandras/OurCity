#pragma once
#include <vector>

#include "Vector.h"
#include "TileRect.h"
#include "SubMap.h"
#include "Tile.h"

class SubMap;
class World
{
private:
	Vector2Data origoOffset;
	int width = 1000;
	int height = 1000;
	TileRectWrapper* tileRectWrapper;
	std::vector<SubMap> submaps;
	//tile-okat tarthatja a world
	std::vector<Tile> tiles;
public:
	World();
	~World();
	Vector2Data getOrigoOffset();
	void reCalculateOrigoOffset();
	std::vector<SubMap>* getSubmaps();
	int getWidth();
	int getHeight();
	TileRectWrapper* getWrapper();
	Vector2Data tileCoorOnWorldPosition(Vector2Data worldPos);
	Tile* getTileOnCoords(int i, int j);
};