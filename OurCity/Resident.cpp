#include "Resident.h"

Resident::Resident(void)
{
	age = 18;
	//workplace = nullptr;
	workplaceID = 0;
	//house = nullptr;
	houseID = 0;
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