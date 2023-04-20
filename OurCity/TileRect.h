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
	// pointer 64 bit - 8 byte
	// id 4 byte
	// típus 1 byte :(
	// ha típusa nem spec akkor id-t vesszük figyelembe
	// ha típusa spec akkor pointert


	// vaaagy
	// ha típusa nem spec
	// akkor a pointert számként értelmezzük
	// számként írjuk felül
	// building = 1 vagy 2 vagy 12342...
	// sima (int) casttal kilehet szedni az adatot

	// ez ideiglenes csak
	Building* building;
	// grafik�ban haszn�lt rect
	TileRect rect;
	// 8 bites integer
	unsigned char texId = 0;
	
	// ez csak 1 byte
	bool hasZone = false;
	unsigned char type = 0;
	// 0 spec
	// 1 house
	// 2 industry
	// 3 service
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