#pragma once
#include "World.h"
#include "Builder.h"
#include "GameTime.h"
#include "AppTime.h"
#include "GameState.h"
#include "ResidentManager.h"
#include "MouseController.h"

#ifndef TESTING
#include "Camera.h"
#endif

class Builder;
class ResidentManager;
class MouseController;
#ifndef TESTING
#endif
class World;
class GameScene
{
private:
	ResidentManager* residentManager;
	World* world;
	Builder* builder;
	GameTime* gameTime;
	GameState* gameState;
	bool gameOver;
#ifndef TESTING
	Camera* camera;
#endif

	int dayCount = 0;
	int monthCount = 0;
	int unhappyYears = 0;

public:
	GameScene(MouseController* mouse);
	~GameScene();

#ifndef TESTING
	Camera* getCamera();
#endif
	World* getWorld();
	Builder* getBuilder();
	GameTime* getGameTime();
	GameState* getGameState();
	ResidentManager* getResidentManager();
	void isGameOver();
	bool getGameOver();

	void update();
	void HandleBurntBuildings();
};