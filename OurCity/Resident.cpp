#include "Resident.h"

Resident::Resident()
{
	age = 18;
	workplace = nullptr;
	house = nullptr;
	currentTax = 0;
	pastTax = 0;
	happiness = 0;
	intention = MOVEIN;
}

void Resident::setAge(int age)
{
	this->age = age;
}

void Resident::setCurrentTax(int tax)
{
	this->currentTax = tax;
}

void Resident::setHouse(House* house)
{
	this->house = house;
}

void Resident::setWorkplace(Workplace* workplace)
{
	this->workplace = workplace;
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

ResidentIntetion Resident::getIntention()
{
	return this->intention;
}

Workplace* Resident::getWorkplace() const
{
	return this->workplace;
}

House* Resident::getHouse() const
{
	return this->house;
}

void Resident::payTax()
{
	// TODO: Implement this
}

void Resident::calculateHappiness()
{
	// TODO: Implement this
}

void Resident::setIntention(ResidentIntetion intention)
{
	this->intention = intention;
}
