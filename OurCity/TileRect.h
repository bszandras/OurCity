#pragma once
#include "Building.h"

class Building;
struct TileRect
{
	unsigned short i;
	unsigned short j;
};
struct Tile
{
	// ez ideiglenes csak
	Building* building;
	// grafikában használt rect
	TileRect rect;
	// 8 bites integer
	unsigned char texId = 0;
	
	// ez csak 1 byte
	bool hasZone = false;

	// itt van még 2 padding byte
	// +
	// +
};

class TileRectWrapper
{
private:
	Tile* rectArr;
	int maxRects = 0;
	int endPointer = 0;

	void ReallocRects();
public:
	TileRectWrapper(int mRects);
	~TileRectWrapper(void);

	int GetLastRectID();
	void AddTile(Tile tile);
	Tile* GetRectsById(int ids[], int rectCount);
	Tile* GetPointerToId(int id);
	void UpdateTexIdById(int id, int texID);
};