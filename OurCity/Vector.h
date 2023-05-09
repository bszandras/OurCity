#pragma once

/*
#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
*/
#include <iostream>
struct Vector2Data
{
	float x = 0;
	float y = 0;
};
struct Vector3Data
{
	float x = 0;
	float y = 0;
	float z = 0;
};
class Vector2Tool
{
public:
	static Vector2Data Scale(Vector2Data original, float num)
	{
		Vector2Data ret = {
			original.x * num,
			original.y * num
		};
		return ret;
	}
	static Vector2Data Add(Vector2Data original, Vector2Data other)
	{
		Vector2Data ret = {
			original.x + other.x,
			original.y + other.y
		};
		return ret;
	}
	static Vector2Data Sub(Vector2Data original, Vector2Data other)
	{
		Vector2Data ret = {
			original.x - other.x,
			original.y - other.x
		};
		return ret;
	}
	static Vector2Data Mul(Vector2Data original, Vector2Data other)
	{

	}
	static Vector2Data Div(Vector2Data original, Vector2Data other)
	{
		Vector2Data ret = {
			original.x / other.x,
			original.y / other.y
		};
		return ret;
	}
	static Vector2Data WorldToScreenSpace(Vector2Data original, Vector2Data windowSize, Vector2Data camPos, float camZoom, Vector2Data worldOrigoOffset)
	{
		Vector2Data ret{ original.x, original.y };
		ret = Scale(ret, camZoom);
		ret = Add(ret, worldOrigoOffset);
		//ret = Sub(ret, Scale(camPos, camZoom));
		ret = {
			ret.x - camPos.x * camZoom,
			ret.y - camPos.y * camZoom
		};

		// normalize to window size
		return ret;
	}
	static Vector2Data ScreenToWorldSpace(Vector2Data original, Vector2Data windowSize, Vector2Data camPos, float camZoom, Vector2Data worldOrigoOffset)
	{
		Vector2Data ret = {
			original.x - windowSize.x / 2,
			original.y - windowSize.y / 2
		};
		//normalize
		ret = Div(ret, windowSize);
		ret = Scale(ret, 2);
		
		ret = {
			ret.x *= windowSize.x / 2,
			ret.y *= windowSize.y / 2
		};
		

		ret = Scale(ret, 1/camZoom);
		ret = {
			ret.x + camPos.x,
			ret.y + -camPos.y
		};

		ret.y = -ret.y;
		return ret;
	}
	/// <summary>
	/// Line�risan interpol�l k�t vektor k�z�tt
	/// </summary>
	/// <param name="a">Els� vektor</param>
	/// <param name="b">M�sodik vektor</param>
	/// <param name="time">Id�, 0-1 k�z�tti �rt�k</param>
	/// <returns>Interpol�lt vektor</returns>
	static Vector2Data Interpolate(Vector2Data a, Vector2Data b, float time)
	{
		if (time < 0)
		{
			time = 0;
		}
		else if (time > 1)
		{
			time = 1;
		}

		Vector2Data ret;
		ret.x = b.x * time + a.x * (1 - time);
		ret.y = b.y * time + a.y * (1 - time);

		return ret;
	}
	/// <summary>
	/// K�t vektor t�vols�g�t lehet ezzel kisz�molni
	/// </summary>
	/// <param name="a">Egyik vektor</param>
	/// <param name="b">M�sik vektor</param>
	/// <returns>T�vols�g</returns>
	static float Distance(Vector2Data a, Vector2Data b)
	{
		float d = sqrt(b.x * a.x + b.y * a.y);
		return d;
	}
};