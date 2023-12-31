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
	// grafik�ban haszn�lt rect
	TileRect rect;
	// 8 bites integer
	unsigned char texId = 0;
	bool onFire = false;
	
	// ez csak 1 byte
	bool hasZone = false;
	unsigned char type = 0;
	// 0 spec
	// 1 house
	// 2 industry
	// 3 service

	// +- érték
	// kevesebb mint 100
	short happinessModifer = 0;
	short fireChance = 0;
	unsigned char publicSafety = 0;
	// ez a norm érték
	// ipar 1-gyel viszi feljebb
	// erdő 1-gyel lejjebb
	unsigned char pollution = 50;
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

	static double distance(Tile* a, Tile* b);
};