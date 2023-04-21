#pragma once


#include <vector>

#include "Vector.h"
#include "TileRect.h"
#include "Camera.h"
#include "World.h"

class World;
#ifndef TESTING
class SubMap
{
private:
	const static int size = 30;
	std::vector<int> rectIds;
	Vector2Data botLeft;
	int realWidth;
	World* world;
public:
	SubMap(Vector2Data bl, int cs, World* w);
	~SubMap();
	std::vector<int> getRectIds();
	void addRect(int i);
	bool shouldBeCulled(Camera* camera);
	int getRectCount();
	Vector3Data* getRectData(TileRectWrapper* wrapper);
	int getRealWidth();
	Vector2Data getBotLeft();

	static int getSize()
	{
		return size;
	}
};
#endif