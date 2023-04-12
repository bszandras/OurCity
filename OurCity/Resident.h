#ifndef RESIDENT_H
#define RESIDENT_H

#include "Workplace.h"
#include "House.h"

enum ResidentIntetion {
	NOINTENTION,
	MOVEIN,
	BUILDHOUSE,
	INDUSTRYWORK,
	BUILDINDUSTRY,
	SERVICEWORK,
	BUILDSERVICE
};

class Workplace;
class House;
class Resident
{
private:
	// senki sem �regebb 128-n�l sz�val lehet 8 bites
	unsigned char age;
	Workplace* workplace;
	House* house;
	int currentTax;
	int pastTax;
	// mivel 0-100 ez�rt lehet 8 bites
	unsigned char happiness;
	// 0,1,2 ez�rt lehet 8 bites
	unsigned char education;
	ResidentIntetion intention;

	// 62 bitet sp�rolunk lakosonk�nt

public:
	Resident(void);

	void setAge(int age);
	void setCurrentTax(int tax);
	void setHouse(House* house);
	void setWorkplace(Workplace* workplace);

	int getAge() const;
	int getPastTax() const;
	int getCurrentTax() const;
	ResidentIntetion getIntention();
	Workplace* getWorkplace() const;
	House* getHouse() const;

	void payTax();
	void calculateHappiness();
	void setIntention(ResidentIntetion intention);
};

#endif
