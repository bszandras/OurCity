#pragma once
#include "Zone.h"
#include "World.h"

class ZoneTools
{
public:
	static int getResidentCount(ZoneStatData* selected, World* w);
	static int getAverageHappiness(ZoneStatData* selected, World* w, ResidentManager* resMan);
	static int getBuildingCount();
	static int getTileCount();
};