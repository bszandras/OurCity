#pragma once
#include "World.h"
#include "Camera.h"
#include "Builder.h"
#include "MouseController.h"
#include "GameTime.h"
#include "AppTime.h"
#include "GameState.h"

class Builder;
class MouseController;
class World;
class GameScene
{
private:
	World* world;
	Camera* camera;
	Builder* builder;
	GameTime* gameTime;
	GameState* gameState;

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