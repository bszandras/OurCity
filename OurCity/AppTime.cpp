#include "AppTime.h"

Time* Time::instance = nullptr;
/// <summary>
/// Applik�ci� glob�lis id� konstruktora
/// </summary>
/// <param name="currTime">Az aktu�lis id� m�sodpercekben</param>
/// <returns></returns>
Time::Time(float currTime)
{
	if (instance != nullptr)
	{
		return;
	}
	instance = this;
	deltaTime = 0;
	time = currTime;
	// scale-t egyel�re nem haszn�ljuk
	scale = 1;
}

Time::~Time()
{
	instance = nullptr;
}

/// <summary>
/// El�r�bb l�pteti az applik�ci� id�t
/// </summary>
/// <param name="currTime">Az aktu�lis id�, amire el�re kell l�pni</param>
void Time::UpdateTime(float currTime)
{
	deltaTime = currTime - time;
	// ez nem okvetlen j�, tud nem defini�lt viselked�st gener�lni
	time += deltaTime * scale;
}
/// <summary>
/// [Deprecated] Id� sebess�g�t �ll�tja
/// </summary>
/// <param name="s">Sebess�g szorz�</param>
void Time::SetScale(float s)
{
	scale = s;
}
/// <summary>
/// Deltatime gettere
/// </summary>
/// <returns></returns>
float Time::getDelta()
{
	return deltaTime;
}
/// <summary>
/// Id� gettere
/// </summary>
/// <returns></returns>
float Time::getFullTime()
{
	return time;
}
