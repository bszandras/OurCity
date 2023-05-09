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

int Statistics::getPopulation()
{
	return population;
}

float Statistics::getAvgAge()
{
	return avgAge;
}

int Statistics::getMoney()
{
	return money;
}

float Statistics::getAvgHappiness()
{
	return avgHappiness;
}

int Statistics::getPensionerCount()
{
	return pensionerCount;
}

float Statistics::getAvgPension()
{
	return avgPension;
}

int Statistics::getHomeless()
{
	return homeless;
}

int Statistics::getPopulationInHouse()
{
	return populationInHouse;
}

int Statistics::getHouseCapacity()
{
	return houseCapacity;
}

int Statistics::getHouseCapacityFree()
{
	return houseCapacityFree;
}

float Statistics::getHouseCapacityPercent()
{
	return houseCapacityPercent;
}

int Statistics::getWorkers()
{
	return workers;
}

int Statistics::getUnemployed()
{
	return unemployed;
}

int Statistics::getWorkCapacity()
{
	return workCapacity;
}

int Statistics::getFactoryCapacity()
{
	return factoryCapacity;
}

int Statistics::getServiceCapacity()
{
	return serviceCapacity;
}

int Statistics::getIndustryWorkers()
{
	return industryWorkers;
}

int Statistics::getServiceWorkers()
{
	return serviceWorkers;
}

float Statistics::getWorkingPercentage()
{
	return workingPercentage;
}

float Statistics::getServiceIndustryBalance()
{
	return serviceIndustryBalance;
}

int Statistics::getHighSchoolEducated()
{
	return highSchoolEducated;
}

int Statistics::getUniversityEducated()
{
	return universityEducated;
}

int Statistics::getUneducated()
{
	return uneducated;
}

int Statistics::getEducated()
{
	return educated;
}

int Statistics::getEducationPercentage()
{
	return educationPercentage;
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
	if (pensionerCount != 0)
	{
		avgPension /= pensionerCount;
	}
	
}

void Statistics::updateHousingStatistics()
{
	homeless = scene->getResidentManager()->getHomeless();
	populationInHouse = scene->getResidentManager()->getResidentCount() - homeless;
	//houseCapacity = scene->getWorld()->getHouses()->size() * 4;
	houseCapacity = 0;
	for (int i = 0; i < scene->getWorld()->getHouses()->size(); i++)
	{
		houseCapacity += scene->getWorld()->getHouses()->at(i).getCapacity();
	}
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
	//workCapacity = scene->getWorld()->getFactories()->size()*8 +
					   //scene->getWorld()->getServBuildings()->size()*6;
	//factoryCapacity = scene->getWorld()->getFactories()->size()*8;
	factoryCapacity = 0;
	serviceCapacity = 0;
	for (int i = 0; i < scene->getWorld()->getFactories()->size(); i++)
	{
		factoryCapacity += scene->getWorld()->getFactories()->at(i).getCapacity();
	}
	//serviceCapacity = scene->getWorld()->getServBuildings()->size()*6;
	for (int i = 0; i < scene->getWorld()->getServBuildings()->size(); i++)
	{
		serviceCapacity += scene->getWorld()->getServBuildings()->at(i).getCapacity();
	}
	workCapacity = factoryCapacity + serviceCapacity;
	workingPercentage = (float)workers / (float)population * 100;

	// ez buzisan mûködik ha leég az összes factory
	/*
	if (scene->getResidentManager()->getServiceCount() == 0)
	{
		serviceIndustryBalance = 1;
	}
	*/
	serviceIndustryBalance = (float)scene->getResidentManager()->getServiceCount() / (float)scene->getResidentManager()->getFactoryCount();
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