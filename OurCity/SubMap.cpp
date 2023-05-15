#include <iostream>
//#include <vector>
#include "SubMap.h"

#ifndef TESTING
#include "Camera.h"
#include "Window.h"
#endif

#include "World.h"

/// <summary>
/// Alrégió konstruktora
/// </summary>
/// <param name="bl">Régió bal alsó sarkának pozíciója</param>
/// <param name="cs">Cellák szélessége</param>
/// <param name="w">Világra mutató pointer</param>
/// <returns></returns>
SubMap::SubMap(Vector2Data bl, int cs, World* w)
{
	botLeft = bl;
	realWidth = size * cs;
	world = w;

	rectIds.reserve(size * size);
}
SubMap::~SubMap()
{

}
/// <summary>
/// Visszaadja a régióba tartozó összes cella ID-ját
/// </summary>
/// <returns></returns>
std::vector<int> SubMap::getRectIds()
{
	return rectIds;
}
/// <summary>
/// Hozzáadja a régióhoz a paraméterben kapott cellaID-t
/// </summary>
/// <param name="i"></param>
void SubMap::addRect(int i)
{
	rectIds.push_back(i);
}
#ifndef TESTING
/// <summary>
/// Ellenõrzi, hogy a régió a képernyõn látszódik-e
/// </summary>
/// <param name="camera">Kamerára mutató pointee</param>
/// <returns>Igaz, ha nem látszódik</returns>
bool SubMap::shouldBeCulled(Camera* camera)
{
	//check if submap should be culled
	Vector2Data windowSize = { Window::instance->getWidth(),Window::instance->getHeight() };
	Vector2Data bl = Vector2Tool::WorldToScreenSpace(botLeft, windowSize, camera->getPosition(), camera->getZoom(), world->getOrigoOffset());
	int padding = (int)(64 * camera->getZoom());

	
	if (bl.y > windowSize.y + padding || bl.x > windowSize.x + padding
		|| bl.y + realWidth * camera->getZoom() < -padding 
		|| bl.x + realWidth * camera->getZoom() < -padding)
	{
		return true;
	}
	return false;
}
#endif
/// <summary>
/// Visszaadja, hogy hány cella tartozik a régióba.
/// Vannak régiók amik nem az általános mennyiséget tárolják.
/// </summary>
/// <returns></returns>
int SubMap::getRectCount()
{
	return rectIds.size();
}
/// <summary>
/// Visszaadja a régióhoz tartozó összes cella megjelenítéshez szükséges adatát
/// </summary>
/// <param name="wrapper">TileWrapper-re mutató pointer</param>
/// <returns></returns>
Vector3Data* SubMap::getRectData(TileRectWrapper* wrapper)
{
	//x, y, texid
	//rects culled first then rest returned
	Vector3Data* d;
	Tile* rects = wrapper->GetRectsById(rectIds.data(), rectIds.size());
	d = new Vector3Data[(rectIds.size())];
	for (int i = 0; i < rectIds.size(); i++)
	{
		int x = rects[i].rect.i;
		int y = rects[i].rect.j;
		int t = rects[i].texId;

		x = (x * 64) + (y * 32);
		y = (y * (64 - 41));
		d[i] = { (float)x,(float)y,(float)t };
	}
	delete rects;
	return d;
}
/// <summary>
/// Visszaadja a régió valódi szélességét/magasságát (régió négyzet alakú)
/// </summary>
/// <returns></returns>
int SubMap::getRealWidth()
{
	return realWidth;
}
/// <summary>
/// Visszaadja a régió balalsó sarkának pozícióját világkoordinátákban
/// </summary>
/// <returns></returns>
Vector2Data SubMap::getBotLeft()
{
	return botLeft;
}