#pragma once
#include "Zone.h"
#include "World.h"
#include <vector>
#include "Resident.h"

class ZoneTools
{
public:
	static int getResidentCount(ZoneStatData* selected, World* w);
	static int getAverageHappiness(ZoneStatData* selected, World* w, ResidentManager* resMan);
	static std::vector<ResidentData> getResidentData(ZoneStatData* selected, World* w, ResidentManager* resMan);
};