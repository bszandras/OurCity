#include <iostream>
//#include <vector>
#include "SubMap.h"

#ifndef TESTING
#include "Camera.h"
#include "Window.h"
#endif

#include "World.h"

/// <summary>
/// Alr�gi� konstruktora
/// </summary>
/// <param name="bl">R�gi� bal als� sark�nak poz�ci�ja</param>
/// <param name="cs">Cell�k sz�less�ge</param>
/// <param name="w">Vil�gra mutat� pointer</param>
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
/// Visszaadja a r�gi�ba tartoz� �sszes cella ID-j�t
/// </summary>
/// <returns></returns>
std::vector<int> SubMap::getRectIds()
{
	return rectIds;
}
/// <summary>
/// Hozz�adja a r�gi�hoz a param�terben kapott cellaID-t
/// </summary>
/// <param name="i"></param>
void SubMap::addRect(int i)
{
	rectIds.push_back(i);
}
#ifndef TESTING
/// <summary>
/// Ellen�rzi, hogy a r�gi� a k�perny�n l�tsz�dik-e
/// </summary>
/// <param name="camera">Kamer�ra mutat� pointee</param>
/// <returns>Igaz, ha nem l�tsz�dik</returns>
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
/// Visszaadja, hogy h�ny cella tartozik a r�gi�ba.
/// Vannak r�gi�k amik nem az �ltal�nos mennyis�get t�rolj�k.
/// </summary>
/// <returns></returns>
int SubMap::getRectCount()
{
	return rectIds.size();
}
/// <summary>
/// Visszaadja a r�gi�hoz tartoz� �sszes cella megjelen�t�shez sz�ks�ges adat�t
/// </summary>
/// <param name="wrapper">TileWrapper-re mutat� pointer</param>
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
/// Visszaadja a r�gi� val�di sz�less�g�t/magass�g�t (r�gi� n�gyzet alak�)
/// </summary>
/// <returns></returns>
int SubMap::getRealWidth()
{
	return realWidth;
}
/// <summary>
/// Visszaadja a r�gi� balals� sark�nak poz�ci�j�t vil�gkoordin�t�kban
/// </summary>
/// <returns></returns>
Vector2Data SubMap::getBotLeft()
{
	return botLeft;
}