#pragma once
#include <vector>
#include "TileRect.h"
#include "Vector.h"

class Overlay
{
private:
	static Overlay* instance;
	Tile* cursor;
	int cursorSize;
public:
	Overlay();
	~Overlay();
	static void Cursor(bool visible, Vector2Data position);
	static void MultiCursor(bool visible, Vector2Data positions[], int count);
	static Tile* getCursor();
	static int getCursorSize();
};
