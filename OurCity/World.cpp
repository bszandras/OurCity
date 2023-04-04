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
			submaps.push_back(SubMap(Vector2Data{(float)(j*64), (float)(i*64)}, 64, this));
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
			tileRectWrapper->AddTile({ {j,i}, texId });

			int horIndex = x / (SubMap::getSize() * 64);
			int vertIndex = y / (SubMap::getSize() * 64);
			int mainIndex = horIndex + (vertIndex * (width + (height / 2)) / SubMap::getSize());

			submaps[mainIndex].addRect(tileRectWrapper->GetLastRectID());

			// tile-t is meg kell csinálni a grafikai reprezentációhoz
			//tiles.push_back({ x,y });

		}
	}

	//töröljük az üres submapokat
	std::vector<SubMap> newSubMaps;
	newSubMaps.reserve(submapReseve/2);
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
	//offsetelni kell, mert a négyzetek bal alsó sarka az origin
	//worldPos.x -= 32;
	//worldPos.y -= 11;

	//int y = worldPos.y / (64 - 41);
	//int x = (worldPos.x - y * 32) / 64;

	int y = round(worldPos.y / (64 - 41));
	int x = round((worldPos.x - y * 32) / 64);

	//std::cout << x << " " << y << std::endl;
	return {(float)x, (float)y};
}

Tile* World::getTileOnCoords(int i, int j)
{
	int index = j * width;
	index += i;
	return &tiles[index];
}
// elcsúsztatott téglalap kijelölés
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

// fix négyzet kijelölés

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


//	TODO isometrikus téglalap
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

// csík kijelölés
/*
std::vector<int> World::tileIdsInArea(Vector2Data botleft, Vector2Data topright)
{
	std::vector<int> returnable;

	int blY = round(botleft.y / (64 - 41));
	int blX = round((botleft.x - blY * 32) / 64);

	int trY = round(topright.y / (64 - 41));
	int trX = round((topright.x - trY * 32) / 64);

	// blx és trx egyenlõ akkor jobbrafel vagy balrale
	// ha nem egyenlõ balrafel vagy jobbrale

	if (blX == trX)
	{
		for (int i = 0; i < trY - blY; i++)
		{
			int id = ();
		}
	}
	else
	{

	}

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

bool World::AddRoad(Tile* t)
{
	return roadGraph.addRoad(t);
}
