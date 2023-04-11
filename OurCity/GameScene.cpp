#include "GameScene.h"

GameScene::GameScene(MouseController* mouse)
{
	world = new World();
	camera = new Camera({(float)world->getWidth()*64*1.5f/2, (float)world->getHeight()*23/2});
	//camera = new Camera();
	builder = new Builder(world->getWrapper(), mouse, world, this);
	residentManager = new ResidentManager(world, builder);
	gameTime = new GameTime();
	gameState = new GameState();
	for (int i = 0; i < 3; i++) {
		residentManager->createResident();
	}
}

GameScene::~GameScene()
{
	delete world;
	delete camera;
	delete builder;
	delete gameTime;
	delete gameState;
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

GameState* GameScene::getGameState()
{
	return gameState;
}


void GameScene::update()
{
	int days = gameTime->update(Time::instance->getDelta());
	for(int i = 0; i < days; i++)
	{
		residentManager->handleIntention();
		residentManager->createResident();
		residentManager->createResident();
		std::cout << "day passed" << std::endl;
	}
}
