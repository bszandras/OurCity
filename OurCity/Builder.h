#pragma once
#include <vector>
#include "TileRect.h"
#include "MouseController.h"
#include "GameScene.h"

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

	ROAD
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
public:
	Builder(TileRectWrapper* wrapper, MouseController* mouse, World* world, GameScene* scene);
	~Builder();

	void ChangeState(BuilderState state, BuilderSubState subState);
	void Build(int where);
	void Highlight(int target);
	void HighlightArea(Vector2Data mouseWorldPosition, World* world);
	void UnHighlightArea();
};