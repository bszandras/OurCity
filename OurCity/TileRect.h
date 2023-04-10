#pragma once
#include "Tile.h"

struct TileRect
{
	unsigned short i;
	unsigned short j;
};
struct Tile
{
	TileRect rect;
	// 8 bites integer
	unsigned char texId = 0;
	Building* building;
	//building
};

class TileRectWrapper
{
private:
	//TileRect* rectArr;
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
	void UpdateTexIdById(int id, int texID);
	//void CreateTileRect(int i, int j, int t);
};