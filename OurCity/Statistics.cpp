#include "Statistics.h"

Statistics* Statistics::instance = nullptr;

Statistics::Statistics(GameScene* gameScene)
{
	scene = gameScene;
}

Statistics::~Statistics()
{
	delete instance;
}

Statistics* Statistics::getInstance()
{
	instance->updateStats();
	return instance;
}

void Statistics::createInstance(GameScene* scene)
{
	if (instance == nullptr)
	{
		instance = new Statistics(scene);
	}
	else return;
}

void Statistics::updateStats()
{
	updateGeneralStatistics();
	updateHousingStatistics();
}

void Statistics::updateGeneralStatistics()
{
	population = scene->getResidentManager()->getResidentCount();
	avgAge = scene->getResidentManager()->getAverageAge();
	money = scene->getGameState()->getMoney();
	avgHappiness = scene->getResidentManager()->getGlobalHappiness();
}

void Statistics::updateHousingStatistics()
{
	homeless = scene->getResidentManager()->getHomeless();
	populationInHouse = scene->getResidentManager()->getResidentCount() - homeless;
	houseCapacity = scene->getWorld()->getHouses()->size() * 4;
	houseCapacityFree = houseCapacity - populationInHouse;
	houseCapacityPercent = (float)populationInHouse / (float)houseCapacity * 100;
}

void Statistics::updateWorkingStatistics()
{
	unemployed = scene->getResidentManager()->getUnemployed();
	workers = scene->getResidentManager()->getServiceWorkerCount() + 
			  scene->getResidentManager()->getFactoryWorkerCount();
	workCapacity = scene->getResidentManager()->getFactoryCount() * 8 +
				   scene->getResidentManager()->getServiceCount() * 6;
}