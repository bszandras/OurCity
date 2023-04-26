#pragma once
#include "World.h"
#include "Camera.h"
#include "Builder.h"
#include "MouseController.h"
#include "GameTime.h"
#include "AppTime.h"
#include "GameState.h"
#include "ResidentManager.h"

class Builder;
class ResidentManager;
class MouseController;
class World;
class GameScene
{
private:
	ResidentManager* residentManager;
	World* world;
	Camera* camera;
	Builder* builder;
	GameTime* gameTime;
	GameState* gameState;

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
	void HandleBurntBuildings();
};