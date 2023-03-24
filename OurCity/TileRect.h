#pragma once

struct TileRect
{
	int i;
	int j;
	int texID;
};

class TileRectWrapper
{
private:
	TileRect* rectArr;
	int maxRects = 0;
	int endPointer = 0;

	void ReallocRects();
public:
	TileRectWrapper(int mRects);
	~TileRectWrapper(void);

	int GetLastRectID();
	void AddRect(TileRect rect);
	TileRect* GetRectsById(int ids[], int rectCount);
	void UpdateTexIdById(int id, int texID);
	void CreateTileRect(int i, int j, int t);
};