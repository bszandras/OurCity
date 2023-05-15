#include<iostream>

#include "TileRect.h"
#include "SubMap.h"
#include <cmath>
/// <summary>
/// Cell�kat t�rol� objektum konstruktora
/// </summary>
/// <param name="mRects">Maximum cellasz�m</param>
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
/// A wrapperhez hozz�adja a param�terk�nt kapott cell�t
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
/// Mem�ri�ban �tmozgatja a cell�kat.
/// Erre akkor van sz�ks�g amikor elfogyott a cell�k t�rol�s�ra sz�nt szabad mem�ria
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
/// Visszaadja a legutolj�ra hozz�adott cella ID-j�t
/// </summary>
/// <returns></returns>
int TileRectWrapper::GetLastRectID()
{
	return endPointer - 1;
}

// EZT CSAK ADAT OLVAS�SRA HASZN�LJUK
// NEM POINTERT AD AZ EREDETI ADATRA HANEM �RT�KET AD VISSZ

/// <summary>
/// Visszaadja a param�terk�nt kapott cellaid-k adatm�solatait
/// </summary>
/// <param name="ids">ID-k</param>
/// <param name="rectCount">ID-k darabsz�ma</param>
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
/// Visszaadja a param�terk�nt kapott ID-hoz tartoz� pointert
/// </summary>
/// <param name="id"></param>
/// <returns></returns>
Tile* TileRectWrapper::GetPointerToId(int id)
{
	return &rectArr[id];
}
/// <summary>
/// Friss�ti a param�terben kapott ID-hoz tartoz� cella text�raID-j�t
/// </summary>
/// <param name="id">Cella ID-ja</param>
/// <param name="texID">�j text�ra sz�m</param>
void TileRectWrapper::UpdateTexIdById(int id, int texID)
{
	rectArr[id].texId = texID;
}
/// <summary>
/// Visszaadja k�t cella k�zti t�vols�got
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
double TileRectWrapper::distance(Tile* a, Tile* b)
{
	return sqrt(pow(b->rect.i - a->rect.i, 2) + pow(b->rect.j - a->rect.j, 2));
}
