#include "ZoneTools.h"

/// <summary>
/// Megszámolja, hogy egy zónában hányan laknak/dolgoznak
/// </summary>
/// <param name="selected">Kiválasztott zóna</param>
/// <param name="w">Világra pointer</param>
/// <returns>Lakosok száma</returns>
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
/// <summary>
/// Kiszámolja, hogy az adott zónában mennyi az átlag elégedettség
/// </summary>
/// <param name="selected">Kiválasztott zóna</param>
/// <param name="w">Világra pointer</param>
/// <param name="resMan">Resident Manager pointer</param>
/// <returns>Átlagos boldogság</returns>
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
			//residents = h.getResidents();
			std::vector<int> ids = h.getResidents();
			for (int j = 0; j < ids.size(); j++)
			{
				residents.push_back(ids[j]);
			}
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
			//residents = h.getWorkers();
			std::vector<int> ids = h.getWorkers();
			for (int j = 0; j < ids.size(); j++)
			{
				residents.push_back(ids[j]);
			}
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
			//residents = h.getWorkers();
			std::vector<int> ids = h.getWorkers();
			for (int j = 0; j < ids.size(); j++)
			{
				residents.push_back(ids[j]);
			}
		}
	}

	for (int i = 0; i < residents.size(); i++)
	{
		if (resMan->getResident(residents[i])->getIntention() != GHOST)
		{
			returnable += resMan->getResident(residents[i])->getHappiness();
		}
		
	}

	if (residents.size() == 0)
	{
		return 0;
	}

	return returnable / residents.size();
}

std::vector<ResidentData> ZoneTools::getResidentData(ZoneStatData* selected, World* w, ResidentManager* resMan)
{
	std::vector<ResidentData> data;

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
			//residents = h.getResidents();
			std::vector<int> ids = h.getResidents();
			for (int j = 0; j < ids.size(); j++)
			{
				residents.push_back(ids[j]);
			}
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
			//residents = h.getWorkers();
			std::vector<int> ids = h.getWorkers();
			for (int j = 0; j < ids.size(); j++)
			{
				residents.push_back(ids[j]);
			}
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
			//residents = h.getWorkers();
			std::vector<int> ids = h.getWorkers();
			for (int j = 0; j < ids.size(); j++)
			{
				residents.push_back(ids[j]);
			}
		}
	}

	//std::cout << residents.size() << std::endl;

	for (int i = 0; i < residents.size(); i++)
	{
		Resident* res = resMan->getResident(residents[i]);
		if (res->getIntention() != GHOST)
		{
			ResidentData d;
			d.num = residents[i];
			d.age = res->getAge();
			d.education = res->getEducation();
			d.pensioner = res->getAge() > 65;
			d.workplace = res->getWorkplace();
			data.push_back(d);
		}

	}

	return data;
}
