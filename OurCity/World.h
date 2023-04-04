#pragma once
#include <vector>

#include "Vector.h"
#include "TileRect.h"
#include "SubMap.h"
#include "Tile.h"
#include "Zone.h"
#include "RoadGraph.h"

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

	std::vector<Zone> HouseZones;
	std::vector<Zone> IndustryZones;
	std::vector<Zone> ServiceZones;

	RoadGraph roadGraph;
	
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
	std::vector<int> tileIdsInArea(Vector2Data botleft, Vector2Data topright);

	void addHouseZone(Zone zone);
	void addIndustryZone(Zone zone);
	void addServiceZone(Zone zone);

	std::vector<Zone>* getHouseZones();
	std::vector<Zone>* getIndustryZones();
	std::vector<Zone>* getServiceZones();

	bool AddRoad(Tile* t);
};