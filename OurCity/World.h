#pragma once
#include <vector>

#include "Vector.h"
#include "TileRect.h"
#include "SubMap.h"
class SubMap;
class World
{
private:
	Vector2Data origoOffset;
	int width = 1000;
	int height = 1000;
	TileRectWrapper* tileRectWrapper;
	std::vector<SubMap> submaps;
public:
	World();
	~World();
	Vector2Data getOrigoOffset();
	void reCalculateOrigoOffset();
	std::vector<SubMap>* getSubmaps();
	int getWidth();
	int getHeight();
	TileRectWrapper* getWrapper();
};