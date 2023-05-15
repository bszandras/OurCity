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
/// Friss�ti a statisztik�kat, majd visszaadja a p�ld�nyt
/// </summary>
/// <returns>Statistics p�ld�ny</returns>
Statistics* Statistics::getInstance()
{
	instance->updateStats();
	return instance;
}

/// <summary>
/// L�trehozza a Statisztika p�ld�nyt, ha m�g nem l�tezik
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
/// Megh�vja az �sszes statisztika friss�t� f�ggv�nyt
/// </summary>
void Statistics::updateStats()
{
	updateGeneralStatistics();
	updateHousingStatistics();
	updateWorkingStatistics();
	updateEducateStatistics();
}

/// <summary>
/// Megadja, hogy h�nyan laknak a v�rosban
/// </summary>
/// <returns>A v�ros lak�inak sz�ma</returns>
int Statistics::getPopulation()
{
	return population;
}

/// <summary>
/// Megadja a v�ros lak�inak �tlag�letkor�t
/// </summary>
/// <returns>A v�ros lak�inak �tlag�letkora</returns>
float Statistics::getAvgAge()
{
	return avgAge;
}

/// <summary>
/// Megadja, hogy a j�t�kosnak mennyi p�nze van
/// </summary>
/// <returns>A j�t�kos egyenlege</returns>
int Statistics::getMoney()
{
	return money;
}

/// <summary>
/// Megadja a v�ros �tlagboldogs�g�t
/// </summary>
/// <returns>A v�ros lak�inak �tlagboldogs�ga</returns>
float Statistics::getAvgHappiness()
{
	return avgHappiness;
}

/// <summary>
/// Megadja, hogy h�ny darab nyugd�jas van a v�rosban
/// </summary>
/// <returns>A v�ros nyugd�jasainak sz�ma</returns>
int Statistics::getPensionerCount()
{
	return pensionerCount;
}

/// <summary>
/// Megadja, hogy mennyi az �tlagnyugd�j
/// </summary>
/// <returns>Az �tlagnyugd�j</returns>
float Statistics::getAvgPension()
{
	return avgPension;
}

/// <summary>
/// Megadja, hogy h�ny hajl�ktalan van a v�rosban
/// </summary>
/// <returns>A hajl�ktalanok sz�ma</returns>
int Statistics::getHomeless()
{
	return homeless;
}

/// <summary>
/// Megadja, hogy h�ny ember lakik h�zban
/// </summary>
/// <returns>A h�zzal rendelkez� lakosok sz�ma</returns>
int Statistics::getPopulationInHouse()
{
	return populationInHouse;
}

/// <summary>
/// Megadja, hogy �sszesen h�ny ember lakhat a v�ros h�zaiban
/// </summary>
/// <returns>A v�ros �sszes h�z�nak a kapacit�sa</returns>
int Statistics::getHouseCapacity()
{
	return houseCapacity;
}

/// <summary>
/// Megadja, hogy h�ny szabad hely van a h�zakban
/// </summary>
/// <returns>H�zak szabad helyeinek sz�ma</returns>
int Statistics::getHouseCapacityFree()
{
	return houseCapacityFree;
}

/// <summary>
/// Megadja, hogy a lak�helyekb�l mennyi van bet�ltve
/// </summary>
/// <returns>H�ny sz�zal�k lak�hely van bet�ltve</returns>
float Statistics::getHouseCapacityPercent()
{
	return houseCapacityPercent;
}

/// <summary>
/// Megadja, hogy h�ny ember dolgozik a v�rosban
/// </summary>
/// <returns>A dolgoz� emberek sz�ma</returns>
int Statistics::getWorkers()
{
	return workers;
}

/// <summary>
/// Megadja, hogy h�ny ember munkan�lk�li
/// </summary>
/// <returns>A munkan�lk�li emberek sz�ma</returns>
int Statistics::getUnemployed()
{
	return unemployed;
}

/// <summary>
/// Megadja, hogy �sszesen h�ny munkahely van a v�rosban
/// </summary>
/// <returns>A munkahelyek sz�ma</returns>
int Statistics::getWorkCapacity()
{
	return workCapacity;
}

/// <summary>
/// Megadja, hogy a gy�rakban �sszesen h�ny ember tud dolgozni
/// </summary>
/// <returns>A gy�rak �sszkapacit�sa</returns>
int Statistics::getFactoryCapacity()
{
	return factoryCapacity;
}

/// <summary>
/// Megadja, hogy kiszolg�l��p�letekben �sszesen h�ny ember tud dolgozni
/// </summary>
/// <returns>A kiszolg�l� �p�letek �sszkapacit�sa</returns>
int Statistics::getServiceCapacity()
{
	return serviceCapacity;
}

/// <summary>
/// Megadja, hogy �sszesen h�nyan dolgoznak gy�rban
/// </summary>
/// <returns>A gy�ri munk�sok sz�ma</returns>
int Statistics::getIndustryWorkers()
{
	return industryWorkers;
}

/// <summary>
/// Megadja, hogy �sszesen h�nyan dolgoznak kiszolg�l��p�letben
/// </summary>
/// <returns>A kiszolg�l� �p�leti munk�sok sz�ma</returns>
int Statistics::getServiceWorkers()
{
	return serviceWorkers;
}

/// <summary>
/// Megadja, hogy a v�ros lak�inak h�ny sz�zal�ka dolgozik
/// </summary>
/// <returns></returns>
float Statistics::getWorkingPercentage()
{
	return workingPercentage;
}

/// <summary>
/// Megadja sz�zal�kosan, hogy az ipari �s a kiszolg�l� �p�letek mennyire vannak kiegyens�lyozva
/// </summary>
/// <returns>Az ipari �s kiszolg�l� �p�letek balansza</returns>
float Statistics::getServiceIndustryBalance()
{
	return serviceIndustryBalance;
}

/// <summary>
/// Megadja, hogy h�ny lakosnak van k�z�piskolai v�gzetts�ge
/// </summary>
/// <returns>A k�z�piskolai v�gzetts�ggel rendelkez� lakosok sz�ma</returns>
int Statistics::getHighSchoolEducated()
{
	return highSchoolEducated;
}

/// <summary>
/// Megadja, hogy h�ny lakosnak van egyetemi v�gzetts�ge
/// </summary>
/// <returns>Az egyetemi v�gzetts�ggel rendelkez� lakosok sz�ma</returns>
int Statistics::getUniversityEducated()
{
	return universityEducated;
}

/// <summary>
/// Megadja, hogy h�ny lakosnak nincs semmilyen iskolai v�gzetts�ge
/// </summary>
/// <returns>A v�gzetts�ggel nem rendelkez�k sz�ma</returns>
int Statistics::getUneducated()
{
	return uneducated;
}

/// <summary>
/// Megadja, hogy �sszesen h�ny ember r�szes�lt valamilyen oktat�sban
/// </summary>
/// <returns>Az oktat�ssal rendelkez�k sz�ma</returns>
int Statistics::getEducated()
{
	return educated;
}

/// <summary>
/// Megadja, hogy a v�ros lak�inak h�ny sz�zal�ka rendelkezik valamilyen oktat�ssal
/// </summary>
/// <returns></returns>
int Statistics::getEducationPercentage()
{
	return educationPercentage;
}

/// <summary>
/// Friss�ti az �ltal�nos statisztik�kat
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
/// Friss�ti a lakhat�ssal kapcsolatos statisztik�kat
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
/// Friss�ti a munk�val kapcsolatos statisztik�kat
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

	// ez buzisan m�k�dik ha le�g az �sszes factory
	/*
	if (scene->getResidentManager()->getServiceCount() == 0)
	{
		serviceIndustryBalance = 1;
	}
	*/
	serviceIndustryBalance = (float)scene->getResidentManager()->getServiceCount() / (float)scene->getResidentManager()->getFactoryCount();
}

/// <summary>
/// Friss�ti az oktat�ssal kapcsolatos statisztik�kat
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