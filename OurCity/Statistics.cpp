#include "Statistics.h"

Statistics* Statistics::instance = nullptr;

/// <summary>
/// Statisztika konstruktor
/// </summary>
/// <param name="gameScene">A gameScene</param>
Statistics::Statistics(GameScene* gameScene)
{
	scene = gameScene;
}

Statistics::~Statistics()
{
	delete instance;
}

/// <summary>
/// Frissíti a statisztikákat, majd visszaadja a példányt
/// </summary>
/// <returns>Statistics példány</returns>
Statistics* Statistics::getInstance()
{
	instance->updateStats();
	return instance;
}

/// <summary>
/// Létrehozza a Statisztika példányt, ha még nem létezik
/// </summary>
/// <param name="scene">A GameScene</param>
void Statistics::createInstance(GameScene* scene)
{
	if (instance == nullptr)
	{
		instance = new Statistics(scene);
	}
	else return;
}

/// <summary>
/// Meghívja az összes statisztika frissítõ függvényt
/// </summary>
void Statistics::updateStats()
{
	updateGeneralStatistics();
	updateHousingStatistics();
	updateWorkingStatistics();
	updateEducateStatistics();
}

/// <summary>
/// Megadja, hogy hányan laknak a városban
/// </summary>
/// <returns>A város lakóinak száma</returns>
int Statistics::getPopulation()
{
	return population;
}

/// <summary>
/// Megadja a város lakóinak átlagéletkorát
/// </summary>
/// <returns>A város lakóinak átlagéletkora</returns>
float Statistics::getAvgAge()
{
	return avgAge;
}

/// <summary>
/// Megadja, hogy a játékosnak mennyi pénze van
/// </summary>
/// <returns>A játékos egyenlege</returns>
int Statistics::getMoney()
{
	return money;
}

/// <summary>
/// Megadja a város átlagboldogságát
/// </summary>
/// <returns>A város lakóinak átlagboldogsága</returns>
float Statistics::getAvgHappiness()
{
	return avgHappiness;
}

/// <summary>
/// Megadja, hogy hány darab nyugdíjas van a városban
/// </summary>
/// <returns>A város nyugdíjasainak száma</returns>
int Statistics::getPensionerCount()
{
	return pensionerCount;
}

/// <summary>
/// Megadja, hogy mennyi az átlagnyugdíj
/// </summary>
/// <returns>Az átlagnyugdíj</returns>
float Statistics::getAvgPension()
{
	return avgPension;
}

/// <summary>
/// Megadja, hogy hány hajléktalan van a városban
/// </summary>
/// <returns>A hajléktalanok száma</returns>
int Statistics::getHomeless()
{
	return homeless;
}

/// <summary>
/// Megadja, hogy hány ember lakik házban
/// </summary>
/// <returns>A házzal rendelkezõ lakosok száma</returns>
int Statistics::getPopulationInHouse()
{
	return populationInHouse;
}

/// <summary>
/// Megadja, hogy összesen hány ember lakhat a város házaiban
/// </summary>
/// <returns>A város összes házának a kapacitása</returns>
int Statistics::getHouseCapacity()
{
	return houseCapacity;
}

/// <summary>
/// Megadja, hogy hány szabad hely van a házakban
/// </summary>
/// <returns>Házak szabad helyeinek száma</returns>
int Statistics::getHouseCapacityFree()
{
	return houseCapacityFree;
}

/// <summary>
/// Megadja, hogy a lakóhelyekbõl mennyi van betöltve
/// </summary>
/// <returns>Hány százalék lakóhely van betöltve</returns>
float Statistics::getHouseCapacityPercent()
{
	return houseCapacityPercent;
}

/// <summary>
/// Megadja, hogy hány ember dolgozik a városban
/// </summary>
/// <returns>A dolgozó emberek száma</returns>
int Statistics::getWorkers()
{
	return workers;
}

/// <summary>
/// Megadja, hogy hány ember munkanélküli
/// </summary>
/// <returns>A munkanélküli emberek száma</returns>
int Statistics::getUnemployed()
{
	return unemployed;
}

/// <summary>
/// Megadja, hogy összesen hány munkahely van a városban
/// </summary>
/// <returns>A munkahelyek száma</returns>
int Statistics::getWorkCapacity()
{
	return workCapacity;
}

/// <summary>
/// Megadja, hogy a gyárakban összesen hány ember tud dolgozni
/// </summary>
/// <returns>A gyárak összkapacitása</returns>
int Statistics::getFactoryCapacity()
{
	return factoryCapacity;
}

/// <summary>
/// Megadja, hogy kiszolgálóépületekben összesen hány ember tud dolgozni
/// </summary>
/// <returns>A kiszolgáló épületek összkapacitása</returns>
int Statistics::getServiceCapacity()
{
	return serviceCapacity;
}

/// <summary>
/// Megadja, hogy összesen hányan dolgoznak gyárban
/// </summary>
/// <returns>A gyári munkások száma</returns>
int Statistics::getIndustryWorkers()
{
	return industryWorkers;
}

/// <summary>
/// Megadja, hogy összesen hányan dolgoznak kiszolgálóépületben
/// </summary>
/// <returns>A kiszolgáló épületi munkások száma</returns>
int Statistics::getServiceWorkers()
{
	return serviceWorkers;
}

/// <summary>
/// Megadja, hogy a város lakóinak hány százaléka dolgozik
/// </summary>
/// <returns></returns>
float Statistics::getWorkingPercentage()
{
	return workingPercentage;
}

/// <summary>
/// Megadja százalékosan, hogy az ipari és a kiszolgáló épületek mennyire vannak kiegyensúlyozva
/// </summary>
/// <returns>Az ipari és kiszolgáló épületek balansza</returns>
float Statistics::getServiceIndustryBalance()
{
	return serviceIndustryBalance;
}

/// <summary>
/// Megadja, hogy hány lakosnak van középiskolai végzettsége
/// </summary>
/// <returns>A középiskolai végzettséggel rendelkezõ lakosok száma</returns>
int Statistics::getHighSchoolEducated()
{
	return highSchoolEducated;
}

/// <summary>
/// Megadja, hogy hány lakosnak van egyetemi végzettsége
/// </summary>
/// <returns>Az egyetemi végzettséggel rendelkezõ lakosok száma</returns>
int Statistics::getUniversityEducated()
{
	return universityEducated;
}

/// <summary>
/// Megadja, hogy hány lakosnak nincs semmilyen iskolai végzettsége
/// </summary>
/// <returns>A végzettséggel nem rendelkezõk száma</returns>
int Statistics::getUneducated()
{
	return uneducated;
}

/// <summary>
/// Megadja, hogy összesen hány ember részesült valamilyen oktatásban
/// </summary>
/// <returns>Az oktatással rendelkezõk száma</returns>
int Statistics::getEducated()
{
	return educated;
}

/// <summary>
/// Megadja, hogy a város lakóinak hány százaléka rendelkezik valamilyen oktatással
/// </summary>
/// <returns></returns>
int Statistics::getEducationPercentage()
{
	return educationPercentage;
}

/// <summary>
/// Frissíti az általános statisztikákat
/// </summary>
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

/// <summary>
/// Frissíti a lakhatással kapcsolatos statisztikákat
/// </summary>
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

/// <summary>
/// Frissíti a munkával kapcsolatos statisztikákat
/// </summary>
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

/// <summary>
/// Frissíti az oktatással kapcsolatos statisztikákat
/// </summary>
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