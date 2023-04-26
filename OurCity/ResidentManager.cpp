#include "ResidentManager.h"
#include <cmath>

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
						// ezek szerint nem lakik sehol mert 0 a haza
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
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i].getHouse() == hosueID)
		{
			residents[i].setHouse(0);
			residents[i].setWorkplace(0);
			residents[i].setIntention(MOVEIN);
		}
	}
}

void ResidentManager::loseJobFactory(int jobID)
{
	for (int i = 0; i < residents.size(); i++)
	{
		if (residents[i].getWorkplace() == jobID)
		{
			residents[i].setWorkplace(0);
			this->factoryCount--;
			this->residents[i].setIntention(INDUSTRYWORK);
			world->getFactory(jobID)->removeWorker(i);
		}
	}
}

void ResidentManager::loseJobService(int jobID)
{
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
					residents[i].setHouse(j+1);
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
			if (residents[i].getHouse() == 0)
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

int ResidentManager::calculateHappiness()
{
	return 0;
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
