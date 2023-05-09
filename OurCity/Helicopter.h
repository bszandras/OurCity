#pragma once
#include "Fire.h"
#include "Vector.h"
class Helicopter
{
private:
	// 0,1,2
	// a rotorok 3 fázisa
	int texID = 0;
	int rotorPhaseLength = 3;
	float moveSpeed = 100;
	Vector2Data home;
	Vector2Data position;
	Vector2Data start;
	Vector2Data end;
	float flightTime;
	float targetTime;
	bool arrived = false;
	Fire* targetFire;
public:
	Helicopter(Vector2Data origin, Vector2Data target, Fire* f);
	~Helicopter();
	void AdvanceRotor();
	void MoveToTarget(float deltaTime);
	void SetTarget(Vector2Data target);
	bool HasArrived();
	Tile getTile();
	Fire* getTargetFire();
	void FireBurned();
	void ReturnHome();
};