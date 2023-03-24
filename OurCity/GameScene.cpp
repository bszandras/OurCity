#include "GameScene.h"

GameScene::GameScene()
{
	world = new World();
	camera = new Camera({(float)world->getWidth()*64*1.5f/2, (float)world->getHeight()*23/2});
	
}

GameScene::~GameScene()
{
}

Camera* GameScene::getCamera()
{
	return camera;
}

World* GameScene::getWorld()
{
	return world;
}
