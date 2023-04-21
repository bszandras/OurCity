#pragma once
#include <vector>
#include "ResidentManager.h"
#include "RoadGraph.h"
#include "Vector.h"
#include "TileRect.h"
#include "SubMap.h"
#include "Tile.h"
#include "Zone.h"
#include "Builder.h"
#include "Fire.h"


#include "BuildingsInclude.h"

class SubMap;
class GameScene;
class RoadGraph;
class ResidentManager;

class World
{
private:
	Vector2Data origoOffset;
	int width = 200;
	int height = 200;
	TileRectWrapper* tileRectWrapper;
	std::vector<SubMap> submaps;
	//tile-okat tarthatja a world
	std::vector<Tile> tiles;

	std::vector<Zone> HouseZones;
	std::vector<Zone> IndustryZones;
	std::vector<Zone> ServiceZones;

	std::vector<House> Houses;
	std::vector<Factory> Factories;
	std::vector<ServiceBuilding> ServBuildings;

	RoadGraph roadGraph;

	std::vector<Fire> fires;

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
	Tile* getNeighboursReadOnly(Tile* origin);
	Tile** getWritableTilePointersInRadius(Tile* origin, int radius);
	Tile** getWritableTilePointersInDirectLineOfSight(Tile* origin, int distance);
	std::vector<int> tileIdsInArea(Vector2Data botleft, Vector2Data topright);

	void addHouseZone(Zone zone);
	void addIndustryZone(Zone zone);
	void addServiceZone(Zone zone);

	House* addHouse(Tile* tile);
	Factory* addFactory(Tile* tile);
	ServiceBuilding* addServBuilding(Tile* tile);

	std::vector<Zone>* getHouseZones();
	std::vector<Zone>* getIndustryZones();
	std::vector<Zone>* getServiceZones();
	
	ZoneStatData getZoneStatsForTile(int tileID);

	std::vector<House>* getHouses();
	std::vector<Factory>* getFactories();
	std::vector<ServiceBuilding>* getServBuildings();

	House* getHouse(int id);
	Factory* getFactory(int id);
	ServiceBuilding* getServBuilding(int id);

	bool AddRoad(Tile* t, GameScene* scene);
	RoadGraph* getRoadGraph();

	int AddFire(Tile* t);
	std::vector<Fire>* getFires();
	void UpdateFires(int deltaHours);
	bool PutOutFire(int tileID);
};