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

class Resident
{
private:
	int age;
	Workplace* workplace;
	House* house;
	int currentTax;
	int pastTax;
	int happiness;
	ResidentIntetion intention;

public:
	Resident();

	void setAge(int age);
	void setCurrentTax(int tax);
	void setHouse(House* house);
	void setWorkplace(Workplace* workplace);

	int getAge() const;
	int getPastTax() const;
	int getCurrentTax() const;
	Workplace* getWorkplace() const;
	House* getHouse() const;

	void payTax();
	void calculateHappiness();
};

#endif
