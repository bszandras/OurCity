#include <iostream>
//#include <vector>
#include "SubMap.h"
#include "Camera.h"
#include "World.h"
#include "Window.h"

SubMap::SubMap(Vector2Data bl, int cs, World* w)
{
	botLeft = bl;
	realWidth = size * cs;
	world = w;
}
SubMap::~SubMap()
{

}
std::vector<int> SubMap::getRectIds()
{
	return rectIds;
}
void SubMap::addRect(int i)
{
	rectIds.push_back(i);
}
bool SubMap::shouldBeCulled(Camera* camera)
{
	//check if submap should be culled
	Vector2Data windowSize = { Window::instance->getWidth(),Window::instance->getHeight() };
	Vector2Data bl = Vector2Tool::WorldToScreenSpace(botLeft, windowSize, camera->getPosition(), camera->getZoom(), world->getOrigoOffset());
	int padding = (int)(64 * camera->getZoom());
	//padding = 0;

	
	if (bl.y > windowSize.y + padding || bl.x > windowSize.x + padding
		|| bl.y + realWidth * camera->getZoom() < -padding 
		|| bl.x + realWidth * camera->getZoom() < -padding)
	{
		return true;
	}
	return false;
}
int SubMap::getRectCount()
{
	return rectIds.size();
}
Vector3Data* SubMap::getRectData(TileRectWrapper* wrapper)
{
	//x, y, texid
	//rects culled first then rest returned
	Vector3Data* d;
	TileRect* rects = wrapper->GetRectsById(rectIds.data(), rectIds.size());
	d = new Vector3Data[(rectIds.size())];
	for (int i = 0; i < rectIds.size(); i++)
	{
		int x = rects[i].i;
		int y = rects[i].j;
		int t = rects[i].texID;

		x = (x * 64) + (y * 32);
		y = (y * (64 - 41));
		d[i] = { (float)x,(float)y,(float)t };
	}
	delete rects;
	return d;
}
int SubMap::getRealWidth()
{
	return realWidth;
}
Vector2Data SubMap::getBotLeft()
{
	return botLeft;
}
/*
int SubMap::getSize()
{
	return size;
}
*/