#pragma once
#include "World.h"
#include "Builder.h"
#include "GameTime.h"
#include "AppTime.h"
#include "GameState.h"
#include "ResidentManager.h"

#ifndef TESTING
#include "MouseController.h"
#include "Camera.h"
#endif

class Builder;
class ResidentManager;
#ifndef TESTING
class MouseController;
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
#ifndef TESTING
	Camera* camera;
#endif

	int dayCount = 0;
	int monthCount = 0;

public:
	GameScene(MouseController* mouse);
	~GameScene();

	Camera* getCamera();
	World* getWorld();
	Builder* getBuilder();
	GameTime* getGameTime();
	GameState* getGameState();

	void update();
};