#include "ResidentManager.h"

ResidentManager::ResidentManager(World* world)
{
	this->world = world;
	this->factoryCount = 0;
	this->serviceCount = 0;
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
		switch(intention)
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
						houses->at(j).addResident(residents[i]);
						//TODO
						//residents[i].setHouse();
						//beköltözik
					}
				}
				if (!movedIn)
				{
					//nincsen szabad hely -> építkezik
					this->residents[i].setIntention(BUILDHOUSE);
				}
				break;
			}
				
			case BUILDHOUSE:
			{
				//van-e lakossági zónában üres tile
								//ha van építkezik
								//egyébként intention movein
				std::vector<Zone>* hZones = this->world->getHouseZones();
				for (int j = 0; j < hZones->size(); j++)
				{
					std::vector<int> zoneTiles = hZones->at(j).getTiles();
					//TODO
					//id alapján?
				}
				break;
			}
				
			case INDUSTRYWORK:
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
