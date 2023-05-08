#ifndef RESIDENT_H
#define RESIDENT_H

#include "Workplace.h"
#include "House.h"
#include "GameState.h"

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
	//Workplace* workplace;
	// ha negatív akkor service, ha pozitív akkor industry
	// 0 a nincs workplace, ezért minden értéket offsetelni kell 1-gyel
	int workplaceID;
	//House* house;
	// -1 a nincs háza
	int houseID;
	int currentTax;
	int pastTax;
	// mivel 0-100 ezért lehet 8 bites
	unsigned char happiness;
	// 0,1,2 ezért lehet 8 bites
	unsigned char education;
	ResidentIntetion intention;
	float deathChance;

	// 62 bitet spórolunk lakosonként

public:
	Resident(void);

	void setAge(int age);
	void setCurrentTax(int tax);
	//void setHouse(House* house);
	void setHouse(int id);
	//void setWorkplace(Workplace* workplace);
	void setWorkplace(int id);
	void setEducation(int ed);

	int getHappiness() const;
	int getAge() const;
	int getPastTax() const;
	int getCurrentTax() const;
	int getEducation() const;
	ResidentIntetion getIntention();
	//Workplace* getWorkplace() const;
	int getWorkplace() const;
	//House* getHouse() const;
	int getHouse() const;
	void updatePastTax();
	void setHappiness(int happiness);
	void setDeathChance(int deathChance);
	int getDeathChance();
	void setIntention(ResidentIntetion intention);
	int calculatePension();
};

#endif
