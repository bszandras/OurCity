#include "GameScene.h"

GameScene::GameScene(MouseController* mouse)
{
	world = new World();
	camera = new Camera({(float)world->getWidth()*64*1.5f/2, (float)world->getHeight()*23/2});
	//camera = new Camera();
	builder = new Builder(world->getWrapper(), mouse, world);
	gameTime = new GameTime();
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

Builder* GameScene::getBuilder()
{
	return builder;
}

GameTime* GameScene::getGameTime()
{
	return gameTime;
}


void GameScene::update()
{
	gameTime->update(Time::instance->getDelta());
}
