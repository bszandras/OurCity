#pragma once
#include "Fire.h"
#include "FireStation.h"
#include "Vector.h"

class Helicopter
{
private:
	// 0,1,2
	// a rotorok 3 fázisa
	int texID = 0;
	int rotorPhaseLength = 3;
	float moveSpeed = 2.5;
	Vector2Data homePosition;
	Vector2Data position;
	Vector2Data start;
	Vector2Data end;
	float flightTime;
	float targetTime;
	bool arrived = false;
	Fire* targetFire;
	FireStation* homeStation = nullptr;
public:
	Helicopter(Vector2Data origin, Vector2Data target, Fire* f, FireStation* home);
	~Helicopter();
	void AdvanceRotor();
	void MoveToTarget(float deltaTime);
	void SetTarget(Vector2Data target);
	bool HasArrived();
	Tile getTile();
	Fire* getTargetFire();
	FireStation* getStation();
	void FireBurned();
	void ReturnHome();
};