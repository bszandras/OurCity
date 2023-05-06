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
	updateWorkingStatistics();
	updateEducateStatistics();
}

void Statistics::updateGeneralStatistics()
{
	population = scene->getResidentManager()->getResidentCount();
	avgAge = scene->getResidentManager()->getAverageAge();
	money = scene->getGameState()->getMoney();
	scene->getResidentManager()->calculateGlobalHappiness();
	scene->getResidentManager()->updateGlobalHappiness();
	avgHappiness = scene->getResidentManager()->getGlobalHappiness();
	pensionerCount = 0;
	avgPension = 0;
	std::vector<Resident> residents = scene->getResidentManager()->getResidents();
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i].getAge() >= 65)
		{
			pensionerCount++;
			avgPension += residents[i].calculatePension();
		}
	}
	avgPension /= pensionerCount;
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
	unemployed = scene->getResidentManager()->getResidentCount()-
					 scene->getResidentManager()->getFactoryCount() -
					 scene->getResidentManager()->getServiceCount();
	workers = scene->getResidentManager()->getFactoryCount() +
				  scene->getResidentManager()->getServiceCount();
	workCapacity = scene->getWorld()->getFactories()->size()*8 +
					   scene->getWorld()->getServBuildings()->size()*6;
	factoryCapacity = scene->getWorld()->getFactories()->size()*8;
	serviceCapacity = scene->getWorld()->getServBuildings()->size()*6;
	workingPercentage = (float)workers / (float)population * 100;
	serviceIndustryBalance = (float)scene->getResidentManager()->getServiceCount() / (float)scene->getResidentManager()->getFactoryCount() * 100;
}

void Statistics::updateEducateStatistics()
{
	highSchoolEducated = 0;
	universityEducated = 0;
	uneducated = 0;

	std::vector<Resident> residents = scene->getResidentManager()->getResidents();

	for (int i = 0; i < residents.size(); i++)
	{
		int education = residents[i].getEducation();
		if (education == 0)
		{
			uneducated++;
		}
		else if (education == 1)
		{
			highSchoolEducated++;
		}
		else if (education == 2)
		{
			universityEducated++;
		}
	}

	educated = highSchoolEducated + universityEducated;
	educationPercentage = (float)educated / (float)population * 100;
}