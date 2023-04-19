#include "World.h"
#include "SubMap.h"
#include "Window.h"

World::World()
{

	origoOffset = { 0,0 };
	reCalculateOrigoOffset();

	tileRectWrapper = new TileRectWrapper(width * height);
	//tiles.reserve(width * height);
	int submapReseve = (height / SubMap::getSize()) * ((width + height / 2) / SubMap::getSize());
	submaps.reserve(submapReseve);

	for (int i = 0; i < height; i += SubMap::getSize())
	{
		for (int j = 0; j < width + (height / 2); j += SubMap::getSize())
		{
			submaps.push_back(SubMap(Vector2Data{ (float)(j * 64), (float)(i * 64) }, 64, this));
		}
	}

	for (unsigned short i = 0; i < height; i++)
	{
		for (unsigned short j = 0; j < width; j++)
		{
			//int x = (i * 64) + j * 32;
			//int y = (j * (64 - 41));
			int x = (j * 64) + i * 32;
			int y = (i * (64 - 41));
			unsigned char texId = 2;
			//tileRectWrapper->AddRect(TileRect{ i,j,texId });

			tileRectWrapper->AddTile({ nullptr, {j,i}, texId });

			int c = rand() % 10;
			if (c == 1)
			{
				Tile* t = tileRectWrapper->GetPointerToId(tileRectWrapper->GetLastRectID());
				Building* b = new Forest(t);
				b->setBuildCost(0);
				t->building = b;
				t->texId = BuilderSubState::FOREST;
			}
			int horIndex = x / (SubMap::getSize() * 64);
			int vertIndex = y / (SubMap::getSize() * 64);
			int mainIndex = horIndex + (vertIndex * (width + (height / 2)) / SubMap::getSize());

			submaps[mainIndex].addRect(tileRectWrapper->GetLastRectID());

			// tile-t is meg kell csin�lni a grafikai reprezent�ci�hoz
			//tiles.push_back({ x,y });

		}
	}

	//t�r�lj�k az �res submapokat
	std::vector<SubMap> newSubMaps;
	newSubMaps.reserve(submapReseve / 2);
	for (int i = 0; i < submaps.size(); i++)
	{
		if (submaps[i].getRectCount() > 0)
		{
			newSubMaps.push_back(submaps[i]);
		}
	}
	submaps = newSubMaps;
}

World::~World()
{
	// TODO destruktor
	delete tileRectWrapper;
}

Vector2Data World::getOrigoOffset()
{
	return origoOffset;
}

void World::reCalculateOrigoOffset()
{
	origoOffset = { Window::instance->getWidth() / 2.0f, Window::instance->getHeight() / 2.0f };
}

std::vector<SubMap>* World::getSubmaps()
{
	return &submaps;
}

int World::getWidth()
{
	return width;
}

int World::getHeight()
{
	return height;
}
TileRectWrapper* World::getWrapper()
{
	return tileRectWrapper;
}

Vector2Data World::tileCoorOnWorldPosition(Vector2Data worldPos)
{
	//offsetelni kell, mert a n�gyzetek bal als� sarka az origin
	//worldPos.x -= 32;
	//worldPos.y -= 11;

	//int y = worldPos.y / (64 - 41);
	//int x = (worldPos.x - y * 32) / 64;

	int y = round(worldPos.y / (64 - 41));
	int x = round((worldPos.x - y * 32) / 64);

	//std::cout << x << " " << y << std::endl;
	return { (float)x, (float)y };
}

// TAPOSÓAKNA!!!!
Tile* World::getTileOnCoords(int i, int j)
{
	int index = j * width;
	index += i;
	return this->tileRectWrapper->GetPointerToId(index);
}

Tile* World::getNeighboursReadOnly(Tile* origin)
{
	Tile* tiles = new Tile[4];

	Tile* t = this->tileRectWrapper->GetPointerToId((origin->rect.j + 1) * width + origin->rect.i - 1);
	tiles[0] = *t;
	t = this->tileRectWrapper->GetPointerToId((origin->rect.j + 1) * width + origin->rect.i);
	tiles[1] = *t;
	t = this->tileRectWrapper->GetPointerToId((origin->rect.j - 1) * width + origin->rect.i);
	tiles[2] = *t;
	t = this->tileRectWrapper->GetPointerToId((origin->rect.j - 1) * width + origin->rect.i + 1);
	tiles[3] = *t;
	return tiles;
}
Tile** World::getWritableTilePointersInRadius(Tile* origin, int radius)
{
	int tileCount = (radius + 1 + radius) * (radius + 1 + radius) - 1;
	std::cout << tileCount << std::endl;
	Tile** returnable = new Tile* [tileCount];

	int originID = origin->rect.j * width + origin->rect.i;
	int index = 0;

	// center oszlop
	for (int i = -radius; i <= radius; i++)
	{
		if (i == 0)
		{
			continue;
		}

		returnable[index] = tileRectWrapper->GetPointerToId(originID + i * width);
		index++;
	}

	// bal oszlopok
	for (int i = 1; i <= radius; i++)
	{
		int firstID = originID - i;
		returnable[index] = tileRectWrapper->GetPointerToId(firstID);
		index++;

		if(index >= tileCount)
		{
			std::cout << "tilecount problem, left col center" << std::endl;
			return returnable;
		}

		// aktuális bal oszlop lefelé
		for (int j = 1; j <= radius - i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID - j * width);
			index++;

			if (index >= tileCount)
			{
				std::cout << "tilecount problem left col down" << std::endl;
				return returnable;
			}
		}

		// aktuális bal oszlop felfelé
		for (int j = 1; j <= radius + i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID + j * width);
			index++;

			if (index >= tileCount)
			{
				std::cout << "tilecount problem left col up" << std::endl;
				return returnable;
			}
		}
	}

	// jobb oszlopok, ugyanaz mint a bal oszlopok, de tükrözve
	for (int i = 1; i <= radius; i++)
	{
		int firstID = originID + i;
		returnable[index] = tileRectWrapper->GetPointerToId(firstID);
		index++;

		if (index >= tileCount)
		{
			std::cout << "tilecount problem right col center" << std::endl;
			return returnable;
		}

		// aktuális jobb oszlop lefelé
		for (int j = 1; j <= radius - i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID + j * width);
			index++;

			if (index >= tileCount)
			{
				std::cout << "tilecount problem right col down" << std::endl;
				return returnable;
			}
		}

		// aktuális bal oszlop felfelé
		for (int j = 1; j <= radius + i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID - j * width);
			index++;

			if (index >= tileCount)
			{
				// itt valamiért utolsónál kiugrik
				// szóval kommentelve marad a safety check :D

				//std::cout << index << std::endl;
				//std::cout << "tilecount problem right col up" << std::endl;
				//return returnable;
			}

		}
	}

	return returnable;
}
Tile** World::getWritableTilePointersInDirectLineOfSight(Tile* origin, int distance)
{
	Tile** returnable = new Tile * [distance * 4];
	int originID = origin->rect.j * width + origin->rect.i;
	int index = 0;

	// vertical direct line of sight
	for (int i = -distance; i <= distance; i++)
	{
		if (i == 0)
		{
			continue;
		}
		returnable[index] = tileRectWrapper->GetPointerToId(originID + i * width);
		index++;

		returnable[index] = tileRectWrapper->GetPointerToId((originID + i * width) - i);
		index++;
	}

	return returnable;
}
// elcs�sztatott t�glalap kijel�l�s
/*
std::vector<int> World::tileIdsInArea(Vector2Data botleft, Vector2Data topright)
{
	std::vector<int> returnable;

	int blY = round(botleft.y / (64 - 41));
	int blX = round((botleft.x - blY * 32) / 64);

	int trY = round(topright.y / (64 - 41));
	int trX = round((topright.x - trY * 32) / 64);

	//int idOffset = 0;

	for (int j = 0; j <= trY - blY; j++)
	{
		for (int i = 0; i <= trX - blX; i++)
		{
			int id = ((blY + j) * width) + blX;
			returnable.push_back(id + i);
		}
	}
	//std::cout << returnable.size() << std::endl;
	return returnable;
}
*/

// fix n�gyzet kijel�l�s
/*
std::vector<int> World::tileIdsInArea(Vector2Data botleft, Vector2Data topright)
{
	std::vector<int> returnable;

	int blY = round(botleft.y / (64 - 41));
	int blX = round((botleft.x - blY * 32) / 64);

	int trY = round(topright.y / (64 - 41));
	int trX = round((topright.x - trY * 32) / 64);


	int collumnOffset = -(trX - blX);
	for (int j = 0; j <= (trX - blX); j++)
	{
		for (int i = 0; i <= trX - blX; i++)
		{
			int id = ((blY - i + j - collumnOffset) * width) + blX;
			if (id >= 0)
			{
				returnable.push_back(id + i);
			}

		}
		collumnOffset += 2;
	}
	return returnable;
}
*/

//	TODO isometrikus t�glalap
/*
std::vector<int> World::tileIdsInArea(Vector2Data botleft, Vector2Data topright)
{
	std::vector<int> returnable;

	int blY = round(botleft.y / (64 - 41));
	int blX = round((botleft.x - blY * 32) / 64);

	int trY = round(topright.y / (64 - 41));
	int trX = round((topright.x - trY * 32) / 64);


	int collumnOffset = -(trX - blX);
	int width = trX - blX;
	int height = width + (trY - blY) - width;
	for (int j = 0; j <= height; j++)
	{
		for (int i = 0; i <= width; i++)
		{
			int id = ((blY - i + j - collumnOffset) * World::width) + blX;
			returnable.push_back(id + i);
		}
		collumnOffset += 2;
	}
	return returnable;
}
*/

// cs�k kijel�l�s

std::vector<int> World::tileIdsInArea(Vector2Data botleft, Vector2Data topright)
{
	std::vector<int> returnable;

	int blY = round(botleft.y / (64 - 41));
	int blX = round((botleft.x - blY * 32) / 64);

	int trY = round(topright.y / (64 - 41));
	int trX = round((topright.x - trY * 32) / 64);

	if (botleft.x < topright.x)
	{
		if (trY > blY)
		{
			for (int i = 0; i < trY - blY + 1; i++)
			{
				int id = (blY + i) * width + blX;
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
		else
		{
			for (int i = 0; i < trX - blX + 1; i++)
			{
				int id = (blY - i) * width + blX + (i * 1);
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
	}
	else
	{
		if (trY > blY)
		{
			for (int i = 0; i < trY - blY + 1; i++)
			{
				int id = (blY + i) * width + blX - (i * 1);
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
		else
		{
			for (int i = blY - trY; i > 0; i--)
			{
				int id = (trY + i) * width + blX;
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
	}
	
	return returnable;
}

void World::addHouseZone(Zone zone)
{
	this->HouseZones.push_back(zone);
}

void World::addIndustryZone(Zone zone)
{
	this->IndustryZones.push_back(zone);
}

void World::addServiceZone(Zone zone)
{
	this->ServiceZones.push_back(zone);
}

House* World::addHouse(Tile* tile)
{
	House h(tile);
	Houses.push_back(h);

	return Houses.data() + Houses.size()-1;
}

Factory* World::addFactory(Tile* tile)
{
	Factory f(tile);
	Factories.push_back(f);
	return &f;
}

ServiceBuilding* World::addServBuilding(Tile* tile)
{
	ServiceBuilding sv(tile);
	ServBuildings.push_back(sv);
	return &sv;
}

std::vector<Zone>* World::getHouseZones()
{
	return &HouseZones;
}

std::vector<Zone>* World::getIndustryZones()
{
	return &IndustryZones;
}

std::vector<Zone>* World::getServiceZones()
{
	return &ServiceZones;
}

std::vector<House>* World::getHouses()
{
	return &Houses;
}

std::vector<Factory>* World::getFactories()
{
	return &Factories;
}

std::vector<ServiceBuilding>* World::getServBuildings()
{
	return &ServBuildings;
}

House* World::getHouse(int id)
{
	return &Houses.at(id);
}

Factory* World::getFactory(int id)
{
	return &Factories.at(id);
}

ServiceBuilding* World::getServBuilding(int id)
{
	return &ServBuildings.at(id);
}

bool World::AddRoad(Tile* t, GameScene* scene)
{
	return roadGraph.addRoad(t, scene->getGameState());;
}

RoadGraph* World::getRoadGraph()
{
	return &roadGraph;
}
