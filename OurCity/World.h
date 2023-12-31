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
#include "Helicopter.h"

#include "BuildingsInclude.h"

class SubMap;
class GameScene;
class RoadGraph;
class ResidentManager;
class FireStation;

class World
{
private:
	Vector2Data origoOffset;
#ifdef TESTING
	int width = 30;
	int height = 30;
#else
	int width = 200;
	int height = 200;
#endif

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

	int baseTax = 500;
	float globalTaxRate;
	float housingTaxRate;
	float industrialTaxRate;
	float serviceTaxRate;

	RoadGraph roadGraph;

	std::vector<Fire> fires;
	std::vector<FireStation*> fireStations;
	std::vector<SpecialBuilding*> burnableBuildings;
	std::vector<int> burntHouses;
	std::vector<int> burntFactories;
	std::vector<int> burntService;
	std::vector<Helicopter*> helicopters;

	std::vector<HighSchool*> highschools;
	std::vector<University*> universities;

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
	Tile** getNeighboursWritablePointers(Tile* origin);
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

	void AddFireStation(FireStation* firestation);
	void RemoveFireStation(FireStation* firestation);
	std::vector<FireStation*>* getFireStations();
	void AddBurnableSpecialBuilding(SpecialBuilding* specialBuilding);
	void RemoveBurnableSpecialBuilding(SpecialBuilding* specialBuilding);
	std::vector<SpecialBuilding*>* getBurnableSpecials();
	int AddFire(Tile* t);
	std::vector<Fire>* getFires();
	void UpdateFires(int deltaDays);
	bool PutOutFire(int tileID);
	void AdvanceHelicopters(float deltaTime);
	void RemoveHelicopter(Helicopter* heli);
	std::vector<Helicopter*>* getHelicopters();

	std::vector<int> getBurntHouses();
	std::vector<int> getBurntFactories();
	std::vector<int> getBurntService();
	void removeBurntBuildings();

	void setHousingTaxRate(double taxRate);
	void setIndustrialTaxRate(double taxRate);
	void setServiceTaxRate(double taxRate);

	int getBaseTax();
	float getGlobalTaxRate();
	float getHousingTaxRate();
	float getIndustrialTaxRate();
	float getServiceTaxRate();

	float* getGlobalTaxRateHandle();
	float* getHousingTaxRateHandle();
	float* getIndustrialTaxRateHandle();
	float* getServiceTaxRateHandle();

	std::vector<HighSchool*>* getHighSchools();
	std::vector<University*>* getUniversities();

	void addHighschool(HighSchool* h);
	void removeHighschool(HighSchool* h);
	void addUniversity(University* uni);
	void removeUniversity(University* uni);

};