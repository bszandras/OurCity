#include "ResidentManager.h"
#include <cmath>
#include <random>

ResidentManager::ResidentManager(World* world, Builder* builder, GameState* gameState)
{
	this->world = world;
	this->builder = builder;
	this->gameState = gameState;
	this->factoryCount = 0;
	this->serviceCount = 0;
	this->globalHappiness = 100;

	std::cout << sizeof(Building) << std::endl;
}

void ResidentManager::createResident()
{
	Resident* r = new Resident();
	r->setCurrentTax(gameState->calculateTax());
	this->residents.push_back(*r);
	delete r;
}

void ResidentManager::updateResidentMonthly()
{
	calculateHousingTax();
	calculateIndustrialTax();
	calculateServiceTax();

}

void ResidentManager::calculateHousingTax()
{
	std::vector<Zone>* houses = world->getHouseZones();
	// Végigmegyunk minden lakozonan
	for (int i = 0; i < houses->size(); i++)
	{
		int sumTax = 0;
		int residentCount = 0;

		int sumPension = 0;
		int pensionerCount = 0;

		// Lekerjuk a zonahoz tartozo tile-ok id-jat
		std::vector<int> tileIds = houses->at(i).getTiles();

		// Vegigmegyunk a tile-okon
		for (int j = 0; j < tileIds.size(); j++)
		{
			Tile* tile = world->getWrapper()->GetPointerToId(tileIds[j]);
			if (tile->type == 1)
			{
				int houseID = (int)tile->building / 24;
				std::cout << "houseID: " << houseID << std::endl;
				std::cout << "housePointer: " << tile->building << std::endl;
				House* h = &(world->getHouses()->at(houseID));
				std::vector<int> residentIds = h->getResidents();

				for (int k = 0; k < residentIds.size(); k++)
				{
					if (residents[residentIds.at(k)].getHouse() == -1)
					{
						// ezek szerint nem lakik sehol mert -1 a haza
						continue;
					}
					if (residents[residentIds.at(k)].getAge() >= 65)
					{
						pensionerCount++;
						sumPension += residents[residentIds.at(k)].getPastTax() / 480;
						continue;
					}
					residents[residentIds.at(k)].updatePastTax();
					residentCount++;
					sumTax += round(residents[residentIds.at(k)].getCurrentTax() * houses->at(i).getTaxRate() * world->getHousingTaxRate());
				}
			}
		}
		std::cout << "[INFO] " << i << ". lakozonaban " << residentCount << "db lakos " <<
			sumTax << " osszegu adot fizet. " << std::endl;
		gameState->income(sumTax);

		std::cout << "[INFO] " << i << ". lakozonaban " << pensionerCount << "db lakos " <<
			sumPension << " osszegu nyugdijat kap. " << std::endl;
		gameState->spendMoney(sumPension);
	}
}

void ResidentManager::calculateIndustrialTax()
{
	std::vector<Zone>* industries = world->getIndustryZones();

	for (int i = 0; i < industries->size(); i++)
	{
		int sumTax = 0;
		int residentCount = 0;

		// Lekerjuk a zonahoz tartozo tile-ok id-jat
		std::vector<int> tileIds = industries->at(i).getTiles();

		// Vegigmegyunk a tile-okon
		for (int j = 0; j < tileIds.size(); j++)
		{
			Tile* tile = world->getWrapper()->GetPointerToId(tileIds[j]);
			if (tile->type == 2)
			{
				int factoryID = (int)tile->building / 24;
				std::cout << "factoryID: " << factoryID << std::endl;
				std::cout << "factoryPointer: " << tile->building << std::endl;
				Factory* h = &(world->getFactories()->at(factoryID));
				std::vector<int> residentIds = h->getWorkers();

				for (int k = 0; k < residentIds.size(); k++)
				{
					if (residents[residentIds.at(k)].getWorkplace() == 0)
					{
						continue;
					}
					residentCount++;
					sumTax += round(residents[residentIds.at(k)].getCurrentTax() * industries->at(i).getTaxRate() * world->getIndustrialTaxRate());
				}
			}
		}
		std::cout << "[INFO] " << i << ". ipari zonaban " << residentCount << "db lakos utan " <<
			sumTax << " osszegu adot kell fizetni. " << std::endl;
		gameState->income(sumTax);
	}
}

void ResidentManager::calculateServiceTax()
{
	std::vector<Zone>* services = world->getServiceZones();

	for (int i = 0; i < services->size(); i++)
	{
		int sumTax = 0;
		int residentCount = 0;

		// Lekerjuk a zonahoz tartozo tile-ok id-jat
		std::vector<int> tileIds = services->at(i).getTiles();

		// Vegigmegyunk a tile-okon
		for (int j = 0; j < tileIds.size(); j++)
		{
			Tile* tile = world->getWrapper()->GetPointerToId(tileIds[j]);

			if (tile->type == 3)
			{
				int serviceID = (int)tile->building / 24;
				std::cout << "serviceID: " << serviceID << std::endl;
				std::cout << "servicePointer: " << tile->building << std::endl;
				ServiceBuilding* h = &(world->getServBuildings()->at(serviceID));
				std::vector<int> residentIds = h->getWorkers();

				for (int k = 0; k < residentIds.size(); k++)
				{
					if (residents[residentIds.at(k)].getWorkplace() == 0)
					{
						continue;
					}
					residentCount++;
					sumTax += round(residents[residentIds.at(k)].getCurrentTax() * services->at(i).getTaxRate() * world->getServiceTaxRate());
				}
			}
		}
		std::cout << "[INFO] " << i << ". szolgaltatasi zonaban " << residentCount << "db lakos utan " <<
			sumTax << " osszegu adot kell fizetni. " << std::endl;
		gameState->income(sumTax);
	}
}

void ResidentManager::recalculateResidentTax()
{
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i].getAge() < 65)
		{
			residents[i].setCurrentTax(gameState->getCurrentTax());
		}
	}
}

void ResidentManager::loseHouse(int hosueID)
{
	House* h = world->getHouse(hosueID);
	std::vector<int> res = h->getResidents();

	for (int i = 0; i < res.size(); i++)
	{
		residents[res[i]].setIntention(MOVEIN);
		residents[res[i]].setHouse(-1);


		//residents[res[i]].setWorkplace(0);
		// industry-ban dolgozik, elveszti a munkályát
		// van egyáltalán munkahelye
		if (residents[res[i]].getWorkplace() != 0)
		{
			if (residents[res[i]].getWorkplace() > 0)
			{
				world->getFactory(residents[res[i]].getWorkplace() - 1)->removeWorker(res[i]);
				this->factoryCount--;
			}
			// service
			else
			{
				world->getServBuilding(abs(residents[res[i]].getWorkplace()) - 1)->removeWorker(res[i]);
				this->serviceCount--;
			}
			residents[res[i]].setWorkplace(0);
		}
		
	}
	/*
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i].getHouse() == hosueID)
		{
			residents[i].setHouse(0);
			residents[i].setIntention(MOVEIN);

			// industry-ban dolgozik, elveszti a munkályát
			if (residents[i].getWorkplace() > 0)
			{
				world->getFactory(residents[i].getWorkplace() - 1)->removeWorker(i);
			}
			// service
			else
			{
				world->getServBuilding(abs(residents[i].getWorkplace()) - 1)->removeWorker(i);
			}
			residents[i].setWorkplace(0);
		}
	}
	*/
}

void ResidentManager::loseJobFactory(int jobID)
{
	Factory* f = world->getFactory(jobID);
	std::vector<int> workers = f->getWorkers();

	for (int i = 0; i < workers.size(); i++)
	{
		residents[workers[i]].setWorkplace(0);
		residents[workers[i]].setIntention(INDUSTRYWORK);
		// factory-ból nem kell kivenni a dolgozóra mutató id-t mert factory kezelve lesz a world-ben
		this->factoryCount--;
	}
	
	/*
	for (int i = 0; i < residents.size(); i++)
	{
		// adott resident iparban dolgozik
		if (residents[i].getWorkplace() > 0)
		{

		}
		if (residents[i].getWorkplace() == jobID)
		{
			residents[i].setWorkplace(0);
			this->factoryCount--;
			this->residents[i].setIntention(INDUSTRYWORK);
			world->getFactory(jobID)->removeWorker(i);
		}
	}
	*/
}

void ResidentManager::loseJobService(int jobID)
{
	ServiceBuilding* f = world->getServBuilding(jobID);
	std::vector<int> workers = f->getWorkers();

	for (int i = 0; i < workers.size(); i++)
	{
		residents[workers[i]].setWorkplace(0);
		residents[workers[i]].setIntention(SERVICEWORK);
		// factory-ból nem kell kivenni a dolgozóra mutató id-t mert factory úgyis törölve lesz
		this->serviceCount--;
	}
	
	/*
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i].getWorkplace() == jobID)
		{
			residents[i].setWorkplace(0);
			this->serviceCount--;
			this->residents[i].setIntention(SERVICEWORK);
			world->getServBuilding(jobID)->removeWorker(i);
		}
	}
	*/
}

void ResidentManager::updateResidentYearly()
{
	int resSize = this->residents.size();
	int highS = 0;
	int uniS = 0;
	int highSCount = world->getHighSchools()->size();
	int uniSCount = world->getUniversities()->size();
	maxEducatedHi = resSize / 2;
	maxEducatedUn = resSize / 4;

	for (int i = 0; i < resSize; i++)
	{
		int age = this->residents[i].getAge() + 1;
		this->residents[i].setAge(age);
		int ed = this->residents[i].getEducation();
		if (ed == 1) 
		{
			highS++;
		}
		else if(ed == 2)
		{
			uniS++;
		}
		if (age >= 65)
		{
			int deathChance = this->residents[i].getDeathChance() + 0.05;
			this->residents[i].setDeathChance(deathChance);
		}
		if (residents[i].getHappiness() < 20)
		{

		}
	}

	if(highSCount > 0)
	{
		if(maxEducatedHi > highS)
		{
			int education = highSCount * 5;
			for(int i = 0; i < resSize; i++)
			{
				int ed = this->residents[i].getEducation();
				if(ed >= 1)
				{
					continue;
				}
				this->residents[i].setEducation(1);
				education--;
				if (education == 0) {
					break;
				}
			}

		}
	}

	if (uniSCount > 0)
	{
		if (maxEducatedUn > uniS)
		{
			int education = uniSCount * 3;
			for (int i = 0; i < resSize; i++)
			{
				int ed = this->residents[i].getEducation();
				if (ed == 2)
				{
					continue;
				}
				this->residents[i].setEducation(2);
				education--;
				if (education == 0) {
					break;
				}
			}

		}
	}

	residentDeathAndMove();
	
}

void ResidentManager::handleIntention()
{
	int resSize = this->residents.size();

	for (int i = 0; i < resSize; i++)
	{
		ResidentIntetion intention = this->residents[i].getIntention();
		switch (this->residents[i].getIntention())
		{
		case NOINTENTION:
			break;
		case MOVEIN:
		{
			std::vector<House>* houses = this->world->getHouses();
			unsigned int hSize = houses->size();
			bool movedIn = false;
			for (unsigned int j = 0; j < hSize; j++)
			{
				if (houses->at(j).moveIn() && !movedIn)
				{
					movedIn = true;
					houses->at(j).addResident(i);
					//residents[i].setHouse(&houses->at(j));
					residents[i].setHouse(j);
					std::cout << "Moved in " << i << std::endl;
					if (this->factoryCount <= this->serviceCount) {
						this->residents[i].setIntention(INDUSTRYWORK);
						//std::cout << "Finding Ind Work " << i << std::endl;
					}
					else {
						this->residents[i].setIntention(SERVICEWORK);
						//std::cout << "Finding Serv Work " << i << std::endl;
					}
					
					break;
				}
			}
			if (residents[i].getHouse() == -1)
			{
				buildHouse(i);
				break;
			}
			break;
		}

		case INDUSTRYWORK:
		{
			std::vector<Factory>* factoryB = this->world->getFactories();
			unsigned int fSize = factoryB->size();
			bool working = false;
			for (unsigned int j = 0; j < fSize; j++)
			{
				if (factoryB->at(j).canWorkHere() && !working)
				{
					working = true;
					//factoryB->at(j).addWorker(&residents[i]);
					factoryB->at(j).addWorker(i);
					//residents[i].setWorkplace(&factoryB->at(j));
					residents[i].setWorkplace(1 * (j+1));
					std::cout << "Found Work Ind" << i << std::endl;
					this->factoryCount += 1;
					this->residents[i].setIntention(NOINTENTION);
					break;
				}
			}
			if (residents[i].getWorkplace() == 0)
			{
				//std::cout << "Building industry work" << std::endl;
				buildFactory(i);
				break;
			}
			break;
		}
		case SERVICEWORK:
		{
				std::vector<ServiceBuilding>* serviceB = this->world->getServBuildings();
				unsigned int sSize = serviceB->size();
				bool workingS = false;
				for (unsigned int j = 0; j < sSize; j++)
				{
					if (serviceB->at(j).canWorkHere() && !workingS)
					{
						workingS = true;
						//serviceB->at(j).addWorker(&residents[i]);
						serviceB->at(j).addWorker(i);
						//residents[i].setWorkplace(&serviceB->at(j));
						residents[i].setWorkplace(-1 * (j+1));
						std::cout << "Found Work Serv" << i << std::endl;
						this->serviceCount += 1;
						this->residents[i].setIntention(NOINTENTION);
						break;
					}
				}
				if (residents[i].getWorkplace() == 0)
				{
					buildService(i);
					break;
				}
				break;
		}
		}
	}
}

void ResidentManager::buildFactory(int i)
{
	std::vector<Zone>* fZones = this->world->getIndustryZones();
	bool builtFact = false;
	for (int j = 0; j < fZones->size(); j++)
	{
		std::vector<int> zoneTiles = fZones->at(j).getTiles();
		for (int k = 0; k < zoneTiles.size(); k++) {
			Tile* t = this->world->getWrapper()->GetPointerToId(zoneTiles.at(k));
			if (t->building == nullptr && t->type == 0) {
				Factory* f = this->builder->BuildFactory(t);
				if (f != nullptr)
				{
					this->residents[i].setIntention(INDUSTRYWORK);
					builtFact = true;
					//std::cout << "Built Work Ind" << i << std::endl;
					break;
				}
			}
		}
		if (builtFact) {
			break;
		}
	}
}

void ResidentManager::buildService(int i)
{
	std::vector<Zone>* sZones = this->world->getServiceZones();
	bool builtServ = false;
	for (int j = 0; j < sZones->size(); j++)
	{
		std::vector<int> zoneTiles = sZones->at(j).getTiles();
		for (int k = 0; k < zoneTiles.size(); k++) {
			Tile* t = this->world->getWrapper()->GetPointerToId(zoneTiles.at(k));
			if (t->building == nullptr && t->type == 0) {
				ServiceBuilding* sv = this->builder->BuildService(t);
				if (sv != nullptr)
				{
					this->residents[i].setIntention(SERVICEWORK);
					//std::cout << "Built Work Serv" << i << std::endl;
					builtServ = true;
					break;
				}
			}
		}
		if (builtServ) {
			break;
		}
	}
}

float ResidentManager::getGlobalHappiness()
{
	return this->globalHappiness;
}

int ResidentManager::residentMoveIn()
{
	int freeSpace = 0;

	std::vector<Zone>* hZones = this->world->getHouseZones();

	for (int j = 0; j < hZones->size(); j++)
	{
		std::vector<int> zoneTiles = hZones->at(j).getTiles();

		for (int k = 0; k < zoneTiles.size(); k++) 
		{
			Tile* t = this->world->getWrapper()->GetPointerToId(zoneTiles.at(k));

			if (t->building == nullptr && t->type == 0) 
			{
				if (world->getRoadGraph()->isAdjacent(t))
				{
					freeSpace++;
				}
			}
			else if (t->type == 1) 
			{
				int id = (int)t->building / 24;
				if(this->world->getHouses()->at(id).moveIn())
				{
					freeSpace++;
				}

			}
		}
	}

	return freeSpace;
}

void ResidentManager::updateGlobalHappiness()
{
	int sumHappiness = 0;
	int sizeR = this->residents.size();
	for (int i = 0; i < sizeR; i++) 
	{
		sumHappiness += this->residents[i].getHappiness();
	}
	this->globalHappiness = sumHappiness / sizeR;
}

void ResidentManager::buildHouse(int i) {
	std::vector<Zone>* hZones = this->world->getHouseZones();
	bool builtHouse = false;
	for (int j = 0; j < hZones->size(); j++)
	{
		std::vector<int> zoneTiles = hZones->at(j).getTiles();
		for (int k = 0; k < zoneTiles.size(); k++) {
			Tile* t = this->world->getWrapper()->GetPointerToId(zoneTiles.at(k));
			if (t->building == nullptr && t->type == 0) {
				House* h = this->builder->BuildHouse(t);
				if (h != nullptr)
				{
					this->residents[i].setIntention(MOVEIN);
					builtHouse = true;
					//std::cout << "Built house " << i << std::endl;
					break;
				}
			}
		}
		if (builtHouse) {
			break;
		}
	}

}

void ResidentManager::calculateHappiness(Resident *res)
{
	int defHappiness = 50;
	int happiness = defHappiness;
		
	// Ellenorizzuk az osszes szukseges feltetelt es azoknak megfeleloen
	// Modositjuk a lakos boldogsagat.

	// Ado merteke alapjan
	if (gameState->getTaxRate() <= 1.0)
	{
		//std::cout << "Az ado alacsony (+20)" << std::endl;
		happiness += 20;
	}
	else
	{
		// (1.1-es szorzó felett) - 15 % (és minden további 0.1 es lépésszer -3 %)
		int defMin = 15;
		int extraMin = (gameState->getTaxRate() - 1.1) * 10 * 3;
		//std::cout << "Az ado magas: -" << defMin + extraMin << std::endl;
		happiness -= defMin + extraMin;
	}
	
	Tile* house = nullptr;
	Tile* workplace = nullptr;
	// Lakohely es munkahely kozti tavolsag alapjan
	if (res->getHouse() != -1)
	{
		house = world->getHouse(res->getHouse())->getTile();
	}
	if (res->getWorkplace() != -1)
	{
		if (res->getWorkplace() < 0)
		{
			// Ha a munkahely negativ, akkor szolgaltatas
			workplace = world->getServBuilding(abs(res->getWorkplace()) - 1)->getTile();
		}
		else if (res->getWorkplace() > 0)
		{
			// Ha a munkahely pozitiv, akkor szolgaltatas
			workplace = world->getFactory(abs(res->getWorkplace()) - 1)->getTile();
		}
	}
		
	if (house != nullptr && workplace != nullptr)
	{
		double distance = world->getWrapper()->distance(house, workplace);
		if (distance <= 30.0)
		{
			happiness += 10;
			//std::cout << "Kozel van a munkahely (+10)" << std::endl;
		}
		else
		{
			happiness -= 10;
			//std::cout << "Messze van a munkahely (-10)" << std::endl;
		}
	}

	/**
	* További cella alapú feltételek:
	* - lakóhelyhez nincs közel ipari épület (+/-)
	* - lakóhely és munkahely közbiztonsága (+/-)
	* - stadionra rálátás (+)
	* - erdőre rálátás (+)		* 
	* Ezeket az adott tile happiness modifyer mezője kezeli
	*/

	int houseModifier = 0;
	int workPlaceModifier = 0;

	if (house != nullptr)
	{
		//std::cout << "Lakohely szennyezettsege: " << house->pollution << std::endl;
		// Van-e a közelben ipari terület?
		if (house->pollution <= 50)
		{
			//std::cout << "Nincs a haz kozeleben ipari epulet +10" << std::endl;
			houseModifier += 10;
		}
		else if (house->pollution > 50)
		{
			//std::cout << "Van a haz kozeleben ipari epulet -10" << std::endl;
			houseModifier -= 10;
		}

		// Közbiztonság (+ 10%), (+ lakosszám / 100000), mivel minél többen vannak, annál
		// Fontosabb, de max 20%
		if (house->publicSafety > 0)
		{
			houseModifier += 10;
			int extra = getResidentCount() / 100000;
			if (extra > 10)
			{
				houseModifier += 10;
				//std::cout << "Van kozbiztonsag a hazanal +10" << std::endl;
			}
			else
			{
				houseModifier += extra;
				//std::cout << "Van kozbiztonsag a hazanal +10+" << extra << std::endl;
			}
		}

		// Stadionra rálátás (ez még a happinessModifiert használja, de csak ez,
		// Szóval ha >0 akkor lát styadionra.
		if (house->happinessModifer > 0)
		{
			houseModifier += 10;
			//std::cout << "Lat staionra hazbol +10" << std::endl;
		}
	}

	if (workplace != nullptr)
	{
		if (workplace->publicSafety > 0)
		{
			workPlaceModifier += 10;
			int extra = getResidentCount() / 100000;
			if (extra > 10)
			{
				workPlaceModifier += 10;
				//std::cout << "Van kozbiztonsag a munkahelyen +10" << std::endl;
			}
			else
			{
				workPlaceModifier += extra;
				//std::cout << "Van kozbiztonsag a munkahelyen: +10" << extra << std::endl;
			}
		}

		if (workplace->happinessModifer > 0)
		{
			workPlaceModifier += 10;
			//std::cout << "Ralat a stadionra a munkahelyrol +10" << std::endl;
		}
	}

	if (workplace == nullptr && house != nullptr)
	{
		//std::cout << "Csak haza van" << std::endl;
		happiness += houseModifier;
	}
	else if (workplace != nullptr && house == nullptr)
	{
		//std::cout << "Ennek nem kene kiirodnia, de ha latod, akkor csak munkahelye van" << std::endl;
		happiness += workPlaceModifier;
	}
	else if (workplace != nullptr && house != nullptr)
	{
		//std::cout << "Van munkahelye es haza is" << std::endl;
		happiness += (houseModifier + workPlaceModifier) / 2;
	}


	// Negatív költségvetés arányosan rontja a boldogságot
	// Legyen mondjuk: 100.000 egységenként -1% (max 10 százalékig)
	int money = gameState->getMoney();
	if (money <= 0)
	{
		int defmin = 0;
		if (money > -1000000)
		{
			defmin = gameState->getMoney() / 100000;
		}
		else
		{
			defmin = -10;
		}
		happiness += defmin;
		//std::cout << "Negativ koltsegvetes nyakonvagta a kedvet :(" << std::endl;
	}

	// Kiegyensúlyozatlan az ipar és a szolgáltatás aránya
	// Legyen mondjuk 0.8 és 1.2 között kiegyensúlyozott
	// Ha kiegyensúlyozatlan akkor -10%
	double factoryRation = (double)factoryCount / (double)serviceCount;
	if (factoryRation < 0.8 || factoryRation > 1.2)
	{
		happiness -= 10;
		//std::cout << "Kiegyensulyozatlan az ipar es a szolgaltatas aranya -10" << std::endl;
	}

	res->setHappiness(happiness);
}

void ResidentManager::calculateGlobalHappiness()
{
	int sumHappiness = 0;
	for (size_t i = 0; i < residents.size(); i++)
	{
		calculateHappiness(&residents[i]);
		sumHappiness += residents[i].getHappiness();
	}
	this->globalHappiness = sumHappiness / residents.size();
}

std::vector<Resident> ResidentManager::getResidents()
{
	return this->residents;
}

int ResidentManager::getFactoryCount()
{
	return this->factoryCount;
}

int ResidentManager::getServiceCount()
{
	return this->serviceCount;
}

void ResidentManager::setFactoryCount(int x)
{
	this->factoryCount = x;
}

void ResidentManager::setServiceCount(int x)
{
	this->serviceCount = x;
}

int ResidentManager::getMaxEducatedUn()
{
	return this->maxEducatedUn;
}

int ResidentManager::getMaxEducatedHi()
{
	return this->maxEducatedHi;
}

int ResidentManager::getResSize()
{
	std::cout << this->residents.size() << std::endl;
	return this->residents.size();
}

void ResidentManager::residentDeathAndMove()
{
	int resSize = residents.size();
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	double f = dis(gen);

	for (int i = 0; i < resSize; i++)
	{
		int age = residents[i].getAge();
		if (age >= 65)
		{
			float chance = this->residents[i].getDeathChance();
			if (f < chance)
			{
				int h = residents[i].getHouse();
				int w = residents[i].getWorkplace();
				this->world->getHouse(h)->removeResident(i);
				int workplaceID = residents[i].getWorkplace();
				if (workplaceID < 0) //service
				{
					workplaceID = abs(workplaceID) - 1;
					this->world->getServBuilding(workplaceID)->removeWorker(i);
					this->serviceCount--;
				}
				else if (workplaceID > 0) //factory
				{
					workplaceID--;
					this->world->getFactory(workplaceID)->removeWorker(i);
					this->factoryCount--;
				}

				residents.erase(residents.begin() + i);
			}
		}
		else
		{
			int happiness = residents[i].getHappiness();
			if (happiness < 20)
			{
				int h = residents[i].getHouse();
				int w = residents[i].getWorkplace();
				this->world->getHouse(h)->removeResident(i);
				int workplaceID = residents[i].getWorkplace();
				if (workplaceID < 0) //service
				{
					workplaceID = abs(workplaceID) - 1;
					this->world->getServBuilding(workplaceID)->removeWorker(i);
					this->serviceCount--;
				}
				else if (workplaceID > 0) //factory
				{
					workplaceID--;
					this->world->getFactory(workplaceID)->removeWorker(i);
					this->factoryCount--;
				}

				residents.erase(residents.begin() + i);
			}
		}

	}
}

Resident* ResidentManager::getResident(int id)
{
	return &residents[id];
}

int ResidentManager::getResidentCount() const
{
	return residents.size();
}

float ResidentManager::getAverageAge() const
{
	float sum = 0.0;
	for (size_t i = 0; i < residents.size(); i++)
	{
		sum += residents[i].getAge();
	}
	return sum / residents.size();
}

int ResidentManager::getHomeless() const
{
	int homeless = 0;
	for (size_t i = 0; i < residents.size(); i++)
	{
		if (residents[i].getHouse() == -1)
		{
			homeless++;
		}
	}
	return homeless;
}