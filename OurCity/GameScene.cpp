#include "GameScene.h"
#include <random>

GameScene::GameScene(MouseController* mouse)
{
	world = new World();
#ifndef TESTING
	camera = new Camera({(float)world->getWidth()*64*1.5f/2, (float)world->getHeight()*23/2});
	//camera = new Camera();
#endif
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
#ifndef TESTING
	delete camera;
#endif
	delete builder;
	delete gameTime;
	delete gameState;
}
#ifndef TESTING
Camera* GameScene::getCamera()
{
	return camera;
}
#endif

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

ResidentManager* GameScene::getResidentManager()
{
	return residentManager;
}


void GameScene::update()
{
	int days = gameTime->update(Time::instance->getDelta());
	for(int i = 0; i < days; i++)
	{
		residentManager->handleIntention();
		residentManager->updateGlobalHappiness();

		//boldogság alapján beköltözés
		int calculateRes = floor(residentManager->getGlobalHappiness() / 10);
		int moving = std::min(calculateRes, residentManager->residentMoveIn());

		for (int i = 0; i < moving; i++)
		{
			residentManager->createResident();
		}

		// tûz lehetõség
		// megszerezzük a világtól, hogy mik gyulladhatnak ki
		// elsõkörben csak lakóházak, ipar és szolgáltatás mert azt alapból eltároljuk
		// ha valami kigyullad, a világ kap egy új fire objektumot
		// fire objektumot a második render pass rendereli
		// updateelünk minden fire objektumot

		// neten talált menõ és jobb random
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
		/*
		for (int n = 0; n < 10; ++n) {
			std::cout << dis(gen) << ' ';
		}
		*/
		// 10% esély tûzre naponta
		double f = dis(gen);
		if (f < 0.1)
		{
			int fires = 0;
			float artificialFireChanceMultiplier = 1;
			// LAKÓHÁZ
			std::vector<House>* houses = world->getHouses();
			for (int i = 0; i < houses->size(); i++)
			{
				double c = dis(gen);
				if (c < (double)houses->at(i).getFireChance() / 100 * artificialFireChanceMultiplier)
				{
					Tile* t = houses->at(i).getTile();
					int succ = world->AddFire(t);
					fires += succ;
					if (succ == 1)
					{
						break;
					}
				}
			}
			// IPAR
			// fire threshhold
			if (fires < 1)
			{
				std::vector<Factory>* factories = world->getFactories();
				for (int i = 0; i < factories->size(); i++)
				{
					if (dis(gen) < (double)factories->at(i).getFireChance() / 100 * artificialFireChanceMultiplier)
					{
						Tile* t = factories->at(i).getTile();
						int succ = world->AddFire(t);
						fires += succ;
						if (succ == 1)
						{
							break;
						}
					}
				}
			}
			// SZOLGÁLTATÁS
			// fire threshhold
			if (fires < 1)
			{
				std::vector<ServiceBuilding>* services = world->getServBuildings();
				for (int i = 0; i < services->size(); i++)
				{
					if (dis(gen) < (double)services->at(i).getFireChance() / 100 * artificialFireChanceMultiplier)
					{
						Tile* t = services->at(i).getTile();
						int succ = world->AddFire(t);
						fires += succ;
						if (succ == 1)
						{
							break;
						}
					}
				}
			}
			// SPEC ÉPÜLETEK
			// fire threshhold
			if (fires < 1)
			{
				std::vector<SpecialBuilding*>* specials = world->getBurnableSpecials();
				for (int i = 0; i < specials->size(); i++)
				{
					if (dis(gen) < (double)specials->at(i)->getFireChance() / 100 * artificialFireChanceMultiplier)
					{
						Tile* t = specials->at(i)->getTile();
						int succ = world->AddFire(t);
						fires += succ;
						if (succ == 1)
						{
							break;
						}
					}
				}
			}
		}

		// std::cout << "day passed" << std::endl;
	}

	if (days != 0)
	{
		dayCount+= days;
		world->UpdateFires(days);
		HandleBurntBuildings();
		residentManager->calculateGlobalHappiness();
		residentManager->updateGlobalHappiness();
		std::cout << "Global happiness: " << residentManager->getGlobalHappiness() << std::endl;
	}
	if (dayCount >= 30)
	{
		residentManager->updateResidentMonthly();
		dayCount -= 30;
		monthCount++;
		//std::cout << "month passed" << std::endl;
	}
	if (monthCount >= 12)
	{
		residentManager->updateResidentYearly();
		monthCount -= 12;
		//std::cout << "year passed" << std::endl;
	}

}

void GameScene::HandleBurntBuildings()
{
	std::vector<int> burntHouses = world->getBurntHouses();
	std::vector<int> burntFact = world->getBurntFactories();
	std::vector<int> burntServ = world->getBurntService();

	int burntHSize = burntHouses.size();
	int burntFSize = burntFact.size();
	int burntSeSize = burntServ.size();

	for (int i = 0; i < burntHSize; i++) {
		residentManager->loseHouse(burntHouses[i]);
	}

	for (int i = 0; i < burntFSize; i++) {
		residentManager->loseJobFactory(burntFact[i]);
	}

	for (int i = 0; i < burntSeSize; i++) {
		residentManager->loseJobService(burntServ[i]);
	}

	world->removeBurntBuildings();


}
