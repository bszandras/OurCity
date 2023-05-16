#include "AppTime.h"

Time* Time::instance = nullptr;
/// <summary>
/// Applikáció globális idõ konstruktora
/// </summary>
/// <param name="currTime">Az aktuális idõ másodpercekben</param>
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
	// scale-t egyelõre nem használjuk
	scale = 1;
}

Time::~Time()
{
	instance = nullptr;
}

/// <summary>
/// Elõrébb lépteti az applikáció idõt
/// </summary>
/// <param name="currTime">Az aktuális idõ, amire elõre kell lépni</param>
void Time::UpdateTime(float currTime)
{
	deltaTime = currTime - time;
	// ez nem okvetlen jó, tud nem definiált viselkedést generálni
	time += deltaTime * scale;
}
/// <summary>
/// [Deprecated] Idõ sebességét állítja
/// </summary>
/// <param name="s">Sebesség szorzó</param>
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
/// Idõ gettere
/// </summary>
/// <returns></returns>
float Time::getFullTime()
{
	return time;
}
