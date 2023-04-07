#include<iostream>

#include "TileRect.h"
#include "SubMap.h"


/*
void TileRectWrapper::CreateTileRect(int i, int j, int t)
{
	TileRect tile;
	tile.i = i;
	tile.j = j;
	tile.texID = t;
	
	AddRect(tile);
}
*/
TileRectWrapper::TileRectWrapper(int mRects)
{
	maxRects = mRects;
	rectArr = new Tile[maxRects];
}
TileRectWrapper::~TileRectWrapper(void)
{
	//delete[] rectArr;
	delete rectArr;
}
void TileRectWrapper::AddTile(Tile tile)
{
	if (endPointer >= maxRects)
	{
		ReallocRects();
	}
	
	rectArr[endPointer] = tile;
	endPointer++;
}
void TileRectWrapper::ReallocRects()
{
	maxRects *= 1.1f;
	Tile* newArr = new Tile[maxRects];
	
	for (int i = 0; i < endPointer; i++)
	{
		newArr[i] = rectArr[i];
	}
	
	delete rectArr;
	rectArr = newArr;
}
int TileRectWrapper::GetLastRectID()
{
	return endPointer - 1;
}
// EZT CSAK ADAT OLVASÁSRA HASZNÁLJUK
// NEM POINTERT AD AZ EREDETI ADATRA HANEM ÉRTÉKET AD VISSZ
Tile* TileRectWrapper::GetRectsById(int ids[], int rectCount)
{
	int idCount = rectCount;
	Tile* returnable = new Tile[idCount];

	for (int i = 0; i < idCount; i++)
	{
		returnable[i] = rectArr[ids[i]];
		//returnable[i] = { rectArr[i].rect.i, rectArr[i].rect.j };
	}

	return returnable;
}
Tile* TileRectWrapper::GetPointerToId(int id)
{
	return &rectArr[id];
}
void TileRectWrapper::UpdateTexIdById(int id, int texID)
{
	rectArr[id].texId = texID;
}

void TileRectWrapper::SetBuilding(int target, Building* building)
{
	//rectArr[target]->building = building;
	rectArr[target].building = building;
}

void TileRectWrapper::SetZone(int target, bool val)
{
	rectArr[target].hasZone = val;
}
