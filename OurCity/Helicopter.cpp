#include "Helicopter.h"

Helicopter::Helicopter(Vector2Data origin, Vector2Data target, Fire* f)
{
	home = origin;
	start = origin;
	end = target;
	targetFire = f;
	targetTime = Vector2Tool::Distance(start, end) / 64;
	flightTime = 0;
}

Helicopter::~Helicopter()
{
}

void Helicopter::AdvanceRotor()
{
	texID++;
	if (texID == rotorPhaseLength)
	{
		texID = 0;
	}
}

void Helicopter::MoveToTarget(float deltaTime)
{
	if (targetFire == nullptr && end.x != home.x && end.y != home.y)
	{
		SetTarget(home);
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

void Helicopter::SetTarget(Vector2Data target)
{
	start = position;
	end = target;
	arrived = false;
	targetTime = Vector2Tool::Distance(start, end) / 80;
	flightTime = 0;
}

bool Helicopter::HasArrived()
{
	return arrived;
}

Tile Helicopter::getTile()
{
	Tile t;
	t.rect.i = position.x;
	t.rect.j = position.y;
	t.texId = texID;
	return t;
}

Fire* Helicopter::getTargetFire()
{
	return targetFire;
}

void Helicopter::FireBurned()
{
	targetFire = nullptr;
}

void Helicopter::ReturnHome()
{
	targetFire = nullptr;
	arrived = false;
	SetTarget(home);
}
