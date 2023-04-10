#include "ResidentManager.h"

ResidentManager::ResidentManager(World* world, Builder* builder)
{
	this->world = world;
	this->builder = builder;
	this->factoryCount = 0;
	this->serviceCount = 0;
}

void ResidentManager::createResident()
{
	Resident* r = new Resident();
	this->residents.push_back(*r);
	delete r;
}

void ResidentManager::updateResident()
{
	int resSize = this->residents.size();

	for (int i = 0; i < resSize; i++)
	{
		this->residents[i].payTax();
		int age = this->residents[i].getAge() + 1;
		this->residents[i].setAge(age);
	}
}

void ResidentManager::handleIntention()
{
	int resSize = this->residents.size();

	for(int i = 0; i < resSize; i++)
	{
		ResidentIntetion intention = this->residents[i].getIntention();
		switch(this->residents[i].getIntention())
		{
			case NOINTENTION:
				break;
			case MOVEIN:
			{
				std::cout << residents[i].getIntention() << std::endl;
				
				std::vector<House>* houses = this->world->getHouses();
				unsigned int hSize = houses->size();
				bool movedIn = false;
				for (unsigned int j = 0; j < hSize; j++)
				{
					if (houses->at(j).moveIn() && !movedIn)
					{
						movedIn = true;
						houses->at(j).addResident(residents[i]);
						//TODO
						residents[i].setHouse(&houses->at(j));
						this->residents[i].setIntention(NOINTENTION);
						std::cout << "Moved in " << i << " " << residents[i].getIntention() << std::endl;
						break;
					}
				}
				if (residents[i].getHouse() == nullptr)
				{
					//nincsen szabad hely -> építkezik
					//this->residents[i].setIntention(BUILDHOUSE);
					buildHouse(i);
					break;
				}
				
			}
				
			case BUILDHOUSE:
			{
				buildHouse(i);
				break;
			}
				
			case INDUSTRYWORK:
				//std::vector<ServiceBuilding>* serviceB =  
				break;
			case BUILDINDUSTRY:
				break;
			case SERVICEWORK:
				break;
			case BUILDSERVICE:
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
				this->residents[i].setIntention(MOVEIN);
				builtHouse = true;
				std::cout << "Built house " << i << std::endl;
				break;
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
