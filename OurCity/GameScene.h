#pragma once
#include "World.h"
#include "Camera.h"
#include "Builder.h"
#include "MouseController.h"

class GameScene
{
private:
	World* world;
	Camera* camera;
	Builder* builder;
public:
	GameScene(MouseController* mouse);
	~GameScene();
	Camera* getCamera();
	World* getWorld();
	Builder* getBuilder();
};