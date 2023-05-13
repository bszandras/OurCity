#include "Helicopter.h"

/// <summary>
/// Tûzoltó helikopter konstruktor
/// </summary>
/// <param name="origin">Kezdõ pozíciója a helinek</param>
/// <param name="target">Célja a helinek</param>
/// <param name="f">Cél tûz</param>
/// <param name="home">Tûzoltóállomás ami otthona</param>
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
/// Eggyel tovább lépteti a rotor animációt
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
/// Mozgatja a helikoptert a célja felé
/// </summary>
/// <param name="deltaTime"></param>
void Helicopter::MoveToTarget(float deltaTime)
{
	if (targetFire == nullptr && end.x != homePosition.x && end.y != homePosition.y)
	{
		SetTarget(homePosition);
	}

	// interpolate már 0-1 idõt kap
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
/// Átállítja a helikopter célját
/// </summary>
/// <param name="target">Új célpozíció</param>
void Helicopter::SetTarget(Vector2Data target)
{
	start = position;
	end = target;
	arrived = false;
	targetTime = Vector2Tool::Distance(start, end) / 80;
	flightTime = 0;
}

/// <summary>
/// Megérkezett-e a helikopter?
/// </summary>
/// <returns></returns>
bool Helicopter::HasArrived()
{
	return arrived;
}

/// <summary>
/// Visszaadja a helikoptert reprezentáló Tile-t
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
/// Visszaadja a helikopter céltûzét
/// </summary>
/// <returns></returns>
Fire* Helicopter::getTargetFire()
{
	return targetFire;
}

/// <summary>
/// Visszaadja a helikopter állomását
/// </summary>
/// <returns></returns>
FireStation* Helicopter::getStation()
{
	return homeStation;
}

/// <summary>
/// Szól a helikopternek, hogy a céltûz eltûnt valami okból
/// </summary>
void Helicopter::FireBurned()
{
	targetFire = nullptr;
}

/// <summary>
/// Hazaküldi a helikoptert
/// </summary>
void Helicopter::ReturnHome()
{
	targetFire = nullptr;
	arrived = false;
	SetTarget(homePosition);
}
