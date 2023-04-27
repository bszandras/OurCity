#include "ZoneTools.h"

int ZoneTools::getResidentCount(ZoneStatData* selected, World* w)
{
	int returnable = 0;
	if (selected->z->getType() == 0)
	{
		for (int i = 0; i < selected->tileCount; i++)
		{
			Tile t = selected->tiles[i];
			if (t.type == 0)
			{
				continue;
			}
			House h = w->getHouses()->at((int)t.building / 24);
			returnable += h.getResidents().size();
		}
	}
	else if (selected->z->getType() == 1)
	{
		for (int i = 0; i < selected->tileCount; i++)
		{
			Tile t = selected->tiles[i];
			if (t.type == 0)
			{
				continue;
			}
			Factory h = w->getFactories()->at((int)t.building / 24);
			returnable += h.getWorkers().size();
		}
	}
	else if (selected->z->getType() == 2)
	{
		for (int i = 0; i < selected->tileCount; i++)
		{
			Tile t = selected->tiles[i];
			if (t.type == 0)
			{
				continue;
			}
			ServiceBuilding h = w->getServBuildings()->at((int)t.building / 24);
			returnable += h.getWorkers().size();
		}
	}
	return returnable;
}

int ZoneTools::getAverageHappiness(ZoneStatData* selected, World* w, ResidentManager* resMan)
{
	int returnable = 0;
	std::vector<int> residents;
	if (selected->z->getType() == 0)
	{
		for (int i = 0; i < selected->tileCount; i++)
		{
			Tile t = selected->tiles[i];
			if (t.type == 0)
			{
				continue;
			}
			House h = w->getHouses()->at((int)t.building / 24);
			residents = h.getResidents();
		}
	}
	else if (selected->z->getType() == 1)
	{
		for (int i = 0; i < selected->tileCount; i++)
		{
			Tile t = selected->tiles[i];
			if (t.type == 0)
			{
				continue;
			}
			Factory h = w->getFactories()->at((int)t.building / 24);
			residents = h.getWorkers();
		}
	}
	else if (selected->z->getType() == 2)
	{
		for (int i = 0; i < selected->tileCount; i++)
		{
			Tile t = selected->tiles[i];
			if (t.type == 0)
			{
				continue;
			}
			ServiceBuilding h = w->getServBuildings()->at((int)t.building / 24);
			residents = h.getWorkers();
		}
	}

	for (int i = 0; i < residents.size(); i++)
	{
		returnable += resMan->getResident(residents[i])->getHappiness();
	}

	return returnable / residents.size();
}
