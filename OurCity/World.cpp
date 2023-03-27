#include "World.h"
#include "SubMap.h"
#include "Window.h"

World::World()
{
	origoOffset = { 0,0 };
	reCalculateOrigoOffset();

	tileRectWrapper = new TileRectWrapper(width * height);
	tiles.reserve(width * height);
	int submapReseve = (height / SubMap::getSize()) * ((width + height / 2) / SubMap::getSize());
	submaps.reserve(submapReseve);

	for (int i = 0; i < height; i += SubMap::getSize())
	{
		for (int j = 0; j < width + (height / 2); j += SubMap::getSize())
		{
			submaps.push_back(SubMap(Vector2Data{(float)(j*64), (float)(i*64)}, 64, this));
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//int x = (i * 64) + j * 32;
			//int y = (j * (64 - 41));
			int x = (j * 64) + i * 32;
			int y = (i * (64 - 41));
			int texId = 4;
			//tileRectWrapper->AddRect(TileRect{ i,j,texId });
			tileRectWrapper->AddRect(TileRect{ j,i,texId });

			int horIndex = x / (SubMap::getSize() * 64);
			int vertIndex = y / (SubMap::getSize() * 64);
			int mainIndex = horIndex + (vertIndex * (width + (height / 2)) / SubMap::getSize());

			submaps[mainIndex].addRect(tileRectWrapper->GetLastRectID());

			// tile-t is meg kell csin�lni a grafikai reprezent�ci�hoz
			tiles.push_back({ x,y });

		}
	}

	//t�r�lj�k az �res submapokat
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

	int y = worldPos.y / (64 - 41);
	int x = (worldPos.x - y * 32) / 64;
	return {(float)x, (float)y};
}

Tile* World::getTileOnCoords(int i, int j)
{
	int index = j * width;
	index += i;
	return &tiles[index];
}
