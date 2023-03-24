#include<iostream>

#include "TileRect.h"
#include "SubMap.h"



void TileRectWrapper::CreateTileRect(int i, int j, int t)
{
	TileRect tile;
	tile.i = i;
	tile.j = j;
	tile.texID = t;
	
	AddRect(tile);
}
TileRectWrapper::TileRectWrapper(int mRects)
{
	maxRects = mRects;
	rectArr = new TileRect[maxRects];
}
TileRectWrapper::~TileRectWrapper(void)
{
	//delete[] rectArr;
}
void TileRectWrapper::AddRect(TileRect rect)
{
	if (endPointer >= maxRects)
	{
		ReallocRects();
	}
	
	rectArr[endPointer] = rect;
	endPointer++;
}
void TileRectWrapper::ReallocRects()
{
	maxRects *= 1.1f;
	TileRect* newArr = new TileRect[maxRects];
	
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
TileRect* TileRectWrapper::GetRectsById(int ids[], int rectCount)
{
	int idCount = rectCount;
	TileRect* returnable = new TileRect[idCount];

	for (int i = 0; i < idCount; i++)
	{
		returnable[i] = rectArr[ids[i]];
	}

	return returnable;
}
void TileRectWrapper::UpdateTexIdById(int id, int texID)
{
	rectArr[id].texID = texID;
}