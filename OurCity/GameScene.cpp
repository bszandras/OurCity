#include "GameScene.h"

GameScene::GameScene(MouseController* mouse)
{
	world = new World();
	camera = new Camera({(float)world->getWidth()*64*1.5f/2, (float)world->getHeight()*23/2});
	//camera = new Camera();
	builder = new Builder(world->getWrapper(), mouse, world, this);
	gameTime = new GameTime();
	gameState = new GameState();
	residentManager = new ResidentManager(world, builder, gameState);
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

	if (days != 0)
	{
		dayCount+= days;
	}
	if (dayCount >= 30)
	{
		residentManager->updateResidentMonthly();
		dayCount -= 30;
		monthCount++;
		std::cout << "month passed" << std::endl;
	}
	if (monthCount >= 12)
	{
		residentManager->updateResidentYearly();
		monthCount -= 12;
		std::cout << "year passed" << std::endl;
	}

}
