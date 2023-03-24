#pragma once
#include "World.h"
#include "Camera.h"
class GameScene
{
private:
	World* world;
	Camera* camera;
public:
	GameScene();
	~GameScene();
	Camera* getCamera();
	World* getWorld();
};