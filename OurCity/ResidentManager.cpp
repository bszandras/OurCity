#include "ResidentManager.h"

ResidentManager::ResidentManager()
{
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
				break;
			case BUILDHOUSE:
				break;
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
