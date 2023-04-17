#include "Resident.h"

Resident::Resident(void)
{
	age = 18;
	workplace = nullptr;
	house = nullptr;
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
	// Csak akkor kell nézni az múltbeli idõt, ha már legalább 45 éves, mert
	// csak az utolsó 20 évet kell figyelembe venni a nyugdíjnál
	if (age >= 45 && age <= 65)
	{
		pastTax += currentTax;
	}
}

void Resident::calculateHappiness(int baseTax)
{
	// Az adó mértéke alapján (ITT LEHET BALANCE-OLNI)
	/*
	* Gyors példa a számoláshoz:
	* Az alap évi adó legyen 500.
	* Ha a játékos nem emel adót (marad 500), akkor nem változik a boldogság
	* Ha például a játékos felemeli az adót 700-ra, akkor ha a boldogság 100-as volt,
	* Akkor az emelés után 100 - (700 - 500) / 100 = 100 - 2 = 98 lesz az új boldogság
	*/
	this->happiness = happiness - (this->currentTax - baseTax) / 100;
}

void Resident::setIntention(ResidentIntetion intention)
{
	this->intention = intention;
}