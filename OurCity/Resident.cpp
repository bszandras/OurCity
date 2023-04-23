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
	// ITT kell be�ll�tani majd, hogy oktat�s alapj�n mennyivel fizet t�bb ad�t.
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
	// Csak akkor kell n�zni az m�ltbeli id�t, ha m�r legal�bb 45 �ves, mert
	// csak az utols� 20 �vet kell figyelembe venni a nyugd�jn�l
	if (age >= 45 && age <= 65)
	{
		pastTax += currentTax;
	}
}

void Resident::calculateHappiness(int baseTax)
{
	// Az ad� m�rt�ke alapj�n (ITT LEHET BALANCE-OLNI)
	/*
	* Gyors p�lda a sz�mol�shoz:
	* Az alap �vi ad� legyen 500.
	* Ha a j�t�kos nem emel ad�t (marad 500), akkor nem v�ltozik a boldogs�g
	* Ha p�ld�ul a j�t�kos felemeli az ad�t 700-ra, akkor ha a boldogs�g 100-as volt,
	* Akkor az emel�s ut�n 100 - (700 - 500) / 100 = 100 - 2 = 98 lesz az �j boldogs�g
	*/
	this->happiness = happiness - (this->currentTax - baseTax) / 100;
}

void Resident::setIntention(ResidentIntetion intention)
{
	this->intention = intention;
}