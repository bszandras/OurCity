#pragma once
#include <vector>
#include "TileRect.h"
#include "MouseController.h"
#include "GameScene.h"
#include "BuildingsInclude.h"

class GameScene;
class MouseController;
class World;

enum BuilderState
{
	NOBUILD,
	ZONE,
	ZONECANCEL,
	BUILDING,
	BUILDINGDESTROY
};
enum BuilderSubState
{
	NONE,
	HOUSINGZONE,
	INDUSTRIALZONE,
	SERVICEZONE,

	ROAD = 14,
	FOREST = 30,
	POLICESTATION = 31,
	FIRESTATION = 32,
	HIGHSCHOOL = 33,
	UNIVERSITY = 34,
	STADIUM = 35,
	HOUSE,
	SERVICE,
	INDRUSTRY
};

class Builder
{
private:
	TileRectWrapper* wrapper;
	MouseController* mouse;
	World* world;
	GameScene* scene;

	BuilderState primaryState = NOBUILD;
	BuilderSubState secondaryState = NONE;

	int currentlyHighlighted = 0;
	int currentTex = 2;

	std::vector<int> areaHighlightedIds;
	std::vector<int> areaHighlightedTexes;

	void BuildSpecBuilding(int where);
	void SelectZone();
	void RemoveTileFromZone(int where);
	bool BuildSpecBuilding(Tile* tile, Building* building, int where, int tex);
	bool BuildBigSpecBuilding(Tile* tile, Building* building, int where, int tex);
	bool DestroySpecBuilding(int where);
public:
	Builder(TileRectWrapper* wrapper, MouseController* mouse, World* world, GameScene* scene);
	~Builder();

	void ChangeState(BuilderState state, BuilderSubState subState);
	int Build(int where);
	void Highlight(int target);
	void HighlightBigBuilding(int base);
	void HighlightArea(Vector2Data mouseWorldPosition, World* world);
	void UnHighlightArea();
	House* BuildHouse(Tile* tile);
	Factory* BuildFactory(Tile* tile);
	ServiceBuilding* BuildService(Tile* tile);

};