#include "ResidentManager.h"

ResidentManager::ResidentManager(World* world, Builder* builder, GameState* gameState)
{
	this->world = world;
	this->builder = builder;
	this->gameState = gameState;
	this->factoryCount = 0;
	this->serviceCount = 0;
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
	int resSize = this->residents.size();
	std::vector<Zone>* houses = world->getHouseZones(); // Az összes ház zóna
	std::vector<Zone>* industries = world->getIndustryZones();
	std::vector<Zone>* services = world->getServiceZones();

	// Végigmegyünk minden egyes lakózónán
	for (size_t i = 0; i < houses->size(); i++)
	{
		// Lekérjük a zónában található Tile-ok ID-ját
		std::vector<int> tileIds = houses->at(i).getTiles();

		// Végigmegyünk a TileID-kon
		for (size_t j = 0; j < tileIds.size(); j++)
		{
			int x = world->getWrapper()->GetPointerToId(tileIds[j])->rect.i;
			int y = world->getWrapper()->GetPointerToId(tileIds[j])->rect.j;

			// Végigmegyünk a lakosokon
			for (size_t k = 0; k < residents.size(); k++)
			{
				if (residents[k].getHouse() == 0)
				{
					// ezek szerint nem lakik sehol mert 0 a háza
					continue;
				}
				//House* h = residents[k].getHouse();
				House* h = world->getHouse(residents[k].getHouse() - 1);
				// Megnézzük, hogy az adott lakos háza a Tile-on van-e
				if (h->getTile() == world->getTileOnCoords(x,y))
				{
					std::cout << "Lakos: " << k << " Haza: " << x << " " << y << std::endl;
				}
			}
		}
	}

}

void ResidentManager::updateResident(Resident* resident)
{
	if (resident->getAge() < 65)
	{
		// A játékos megkapja az adó összegét
		gameState->income(resident->getCurrentTax());
		resident->payTax();
	}
	else
	{
		// A játékos nyugdíjat fizet a lakosnak
		// 20 évnyi munka = 240 hónapnyu munka és ha még annak is a fele, akkor 480 az osztó
		gameState->spendMoney(resident->getPastTax() / 480);
	}
	resident->calculateHappiness();
}

void ResidentManager::updateResidentYearly()
{
	int resSize = this->residents.size();

	for (int i = 0; i < resSize; i++)
	{
		int age = this->residents[i].getAge() + 1;
		this->residents[i].setAge(age);
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
						std::cout << "Finding Ind Work " << i << std::endl;
					}
					else {
						this->residents[i].setIntention(SERVICEWORK);
						std::cout << "Finding Serv Work " << i << std::endl;
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
					residents[i].setWorkplace(-1 * (j+1));
					std::cout << "Found Work Ind" << i << std::endl;
					this->factoryCount += 1;
					this->residents[i].setIntention(NOINTENTION);
					break;
				}
			}
			if (residents[i].getWorkplace() == 0)
			{
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
						residents[i].setWorkplace(j+1);
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
			if (t->building == nullptr) {
				Factory* f = this->builder->BuildFactory(t);
				if (f != nullptr)
				{
					this->residents[i].setIntention(INDUSTRYWORK);
					builtFact = true;
					std::cout << "Built Work Ind" << i << std::endl;
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
			if (t->building == nullptr) {
				ServiceBuilding* sv = this->builder->BuildService(t);
				if (sv != nullptr)
				{
					this->residents[i].setIntention(SERVICEWORK);
					std::cout << "Built Work Serv" << i << std::endl;
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

void ResidentManager::buildHouse(int i) {
	std::vector<Zone>* hZones = this->world->getHouseZones();
	bool builtHouse = false;
	for (int j = 0; j < hZones->size(); j++)
	{
		std::vector<int> zoneTiles = hZones->at(j).getTiles();
		for (int k = 0; k < zoneTiles.size(); k++) {
			Tile* t = this->world->getWrapper()->GetPointerToId(zoneTiles.at(k));
			if (t->building == nullptr) {
				House* h = this->builder->BuildHouse(t);
				if (h != nullptr)
				{
					this->residents[i].setIntention(MOVEIN);
					builtHouse = true;
					std::cout << "Built house " << i << std::endl;
					break;
				}
			}
		}
		if (builtHouse) {
			break;
		}
	}

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
