#include "Resident.h"
#include <cmath>

Resident::Resident(void)
{
	age = 18;
	//workplace = nullptr;
	workplaceID = 0;
	//house = nullptr;
	houseID = -1;
	currentTax = 0;
	pastTax = 0;
	happiness = 100;
	education = 0;
	intention = MOVEIN;
}

void Resident::setAge(int age)
{
	this->age = age;
}

void Resident::setCurrentTax(int tax)
{
	// ITT kell beállítani majd, hogy oktatás alapján mennyivel fizet több adót.
	switch (education)
	{
	case 1:
		currentTax = round(tax * 1.1);
		break;
	case 2:
		currentTax = round(tax * 1.2);
		break;
	default:
		currentTax = tax;
		break;
	}
}

void Resident::setHouse(int id)
{
	//this->house = house;
	houseID = id;
}

void Resident::setWorkplace(int id)
{
	//this->workplace = workplace;
	workplaceID = id;
}

void Resident::setEducation(int ed)
{
	this->education = ed;
}

int Resident::getHappiness() const
{
	return this->happiness;
}

int Resident::getAge() const
{
	return this->age;
}

int Resident::getPastTax() const
{
	return this->pastTax;
}

int Resident::getCurrentTax() const
{
	return this->currentTax;
}

int Resident::getEducation() const
{
	return this->education;
}

ResidentIntetion Resident::getIntention()
{
	return this->intention;
}

int Resident::getWorkplace() const
{
	//return this->workplace;
	return workplaceID;
}

int Resident::getHouse() const
{
	//return this->house;
	return houseID;
}

void Resident::updatePastTax()
{
	if (age >= 45 && age <= 65)
	{
		pastTax += currentTax;

	}
}

void Resident::setHappiness(int happiness)
{
	this->happiness = happiness;
}



void Resident::setIntention(ResidentIntetion intention)
{
	this->intention = intention;
}

int Resident::calculatePension()
{
	return pastTax / 480;
}
