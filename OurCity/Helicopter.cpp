#include "Helicopter.h"

/// <summary>
/// T�zolt� helikopter konstruktor
/// </summary>
/// <param name="origin">Kezd� poz�ci�ja a helinek</param>
/// <param name="target">C�lja a helinek</param>
/// <param name="f">C�l t�z</param>
/// <param name="home">T�zolt��llom�s ami otthona</param>
/// <returns></returns>
Helicopter::Helicopter(Vector2Data origin, Vector2Data target, Fire* f, FireStation* home)
{
	//home = origin;
	start = origin;
	end = target;
	targetFire = f;
	targetTime = Vector2Tool::Distance(start, end) / 64;
	flightTime = 0;
	homeStation = home;
	TileRect rect = homeStation->getTile()->rect;
	homePosition.x = (rect.i * 64) + (rect.j * 32);
	homePosition.y = (rect.j * (64 - 41));
}

Helicopter::~Helicopter()
{
}

/// <summary>
/// Eggyel tov�bb l�pteti a rotor anim�ci�t
/// </summary>
void Helicopter::AdvanceRotor()
{
	texID++;
	if (texID == rotorPhaseLength)
	{
		texID = 0;
	}
}

/// <summary>
/// Mozgatja a helikoptert a c�lja fel�
/// </summary>
/// <param name="deltaTime"></param>
void Helicopter::MoveToTarget(float deltaTime)
{
	if (targetFire == nullptr && end.x != homePosition.x && end.y != homePosition.y)
	{
		SetTarget(homePosition);
	}

	// interpolate m�r 0-1 id�t kap
	// position = interpolate
	flightTime += deltaTime * moveSpeed * moveSpeed / targetTime;

	float t = flightTime / targetTime;
	Vector2Data newPos = Vector2Tool::Interpolate(start, end, t);
	position = newPos;

	if (t > 0.95)
	{
		arrived = true;
	}
	else
	{
		arrived = false;
	}
}

/// <summary>
/// �t�ll�tja a helikopter c�lj�t
/// </summary>
/// <param name="target">�j c�lpoz�ci�</param>
void Helicopter::SetTarget(Vector2Data target)
{
	start = position;
	end = target;
	arrived = false;
	targetTime = Vector2Tool::Distance(start, end) / 80;
	flightTime = 0;
}

/// <summary>
/// Meg�rkezett-e a helikopter?
/// </summary>
/// <returns></returns>
bool Helicopter::HasArrived()
{
	return arrived;
}

/// <summary>
/// Visszaadja a helikoptert reprezent�l� Tile-t
/// </summary>
/// <returns></returns>
Tile Helicopter::getTile()
{
	Tile t;
	t.rect.i = position.x;
	t.rect.j = position.y;
	t.texId = texID;
	return t;
}

/// <summary>
/// Visszaadja a helikopter c�lt�z�t
/// </summary>
/// <returns></returns>
Fire* Helicopter::getTargetFire()
{
	return targetFire;
}

/// <summary>
/// Visszaadja a helikopter �llom�s�t
/// </summary>
/// <returns></returns>
FireStation* Helicopter::getStation()
{
	return homeStation;
}

/// <summary>
/// Sz�l a helikopternek, hogy a c�lt�z elt�nt valami okb�l
/// </summary>
void Helicopter::FireBurned()
{
	targetFire = nullptr;
}

/// <summary>
/// Hazak�ldi a helikoptert
/// </summary>
void Helicopter::ReturnHome()
{
	targetFire = nullptr;
	arrived = false;
	SetTarget(homePosition);
}
