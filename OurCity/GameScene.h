#pragma once
#include "World.h"
#include "Camera.h"
#include "Builder.h"
#include "MouseController.h"
#include "GameTime.h"
#include "AppTime.h"

class GameScene
{
private:
	World* world;
	Camera* camera;
	Builder* builder;
	GameTime* gameTime;
public:
	GameScene(MouseController* mouse);
	~GameScene();

	Camera* getCamera();
	World* getWorld();
	Builder* getBuilder();

	void update();
};