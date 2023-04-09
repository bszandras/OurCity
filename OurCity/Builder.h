#pragma once
#include <vector>
#include "TileRect.h"
#include "MouseController.h"

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
	ROAD,
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

	BuilderState primaryState = NOBUILD;
	BuilderSubState secondaryState = NONE;

	int currentlyHighlighted = 0;
	int currentTex = 2;

	std::vector<int> areaHighlightedIds;
	std::vector<int> areaHighlightedTexes;

	void BuildSpecBuilding(int where);
	void SelectZone();
public:
	Builder(TileRectWrapper* wrapper, MouseController* mouse, World* world);
	~Builder();

	void ChangeState(BuilderState state, BuilderSubState subState);
	void Build(int where);
	void Highlight(int target);
	void HighlightArea(Vector2Data mouseWorldPosition, World* world);
	void UnHighlightArea();
};