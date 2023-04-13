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
	// senki sem öregebb 128-nál szóval lehet 8 bites
	unsigned char age;
	Workplace* workplace;
	House* house;
	int currentTax;
	int pastTax;
	// mivel 0-100 ezért lehet 8 bites
	unsigned char happiness;
	// 0,1,2 ezért lehet 8 bites
	unsigned char education;
	ResidentIntetion intention;

	// 62 bitet spórolunk lakosonként

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
