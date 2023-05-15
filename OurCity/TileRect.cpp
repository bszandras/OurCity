#include<iostream>

#include "TileRect.h"
#include "SubMap.h"
#include <cmath>
/// <summary>
/// Cellákat tároló objektum konstruktora
/// </summary>
/// <param name="mRects">Maximum cellaszám</param>
/// <returns></returns>
TileRectWrapper::TileRectWrapper(int mRects)
{
	maxRects = mRects;
	rectArr = new Tile[maxRects];
}
TileRectWrapper::~TileRectWrapper(void)
{
	delete rectArr;
}
/// <summary>
/// A wrapperhez hozzáadja a paraméterként kapott cellát
/// </summary>
/// <param name="tile"></param>
void TileRectWrapper::AddTile(Tile tile)
{
	if (endPointer >= maxRects)
	{
		ReallocRects();
	}
	
	rectArr[endPointer] = tile;
	endPointer++;
}
/// <summary>
/// Memóriában átmozgatja a cellákat.
/// Erre akkor van szükség amikor elfogyott a cellák tárolására szánt szabad memória
/// </summary>
void TileRectWrapper::ReallocRects()
{
	maxRects *= 1.1f;
	Tile* newArr = new Tile[maxRects];
	
	for (int i = 0; i < endPointer; i++)
	{
		newArr[i] = rectArr[i];
	}
	
	delete rectArr;
	rectArr = newArr;
}
/// <summary>
/// Visszaadja a legutoljára hozzáadott cella ID-ját
/// </summary>
/// <returns></returns>
int TileRectWrapper::GetLastRectID()
{
	return endPointer - 1;
}

// EZT CSAK ADAT OLVASÁSRA HASZNÁLJUK
// NEM POINTERT AD AZ EREDETI ADATRA HANEM ÉRTÉKET AD VISSZ

/// <summary>
/// Visszaadja a paraméterként kapott cellaid-k adatmásolatait
/// </summary>
/// <param name="ids">ID-k</param>
/// <param name="rectCount">ID-k darabszáma</param>
/// <returns></returns>
Tile* TileRectWrapper::GetRectsById(int ids[], int rectCount)
{
	int idCount = rectCount;
	Tile* returnable = new Tile[idCount];

	for (int i = 0; i < idCount; i++)
	{
		returnable[i] = rectArr[ids[i]];
	}

	return returnable;
}
/// <summary>
/// Visszaadja a paraméterként kapott ID-hoz tartozó pointert
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
Tile* TileRectWrapper::GetPointerToId(int id)
{
	return &rectArr[id];
}
/// <summary>
/// Frissíti a paraméterben kapott ID-hoz tartozó cella textúraID-ját
/// </summary>
/// <param name="id">Cella ID-ja</param>
/// <param name="texID">Új textúra szám</param>
void TileRectWrapper::UpdateTexIdById(int id, int texID)
{
	rectArr[id].texId = texID;
}
/// <summary>
/// Visszaadja két cella közti távolságot
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
double TileRectWrapper::distance(Tile* a, Tile* b)
{
	return sqrt(pow(b->rect.i - a->rect.i, 2) + pow(b->rect.j - a->rect.j, 2));
}
