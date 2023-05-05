#ifndef STATISTICS_H
#define STATISTICS_H

#include "GameScene.h"

class Statistics
{
private:
	// Statisztikai adatok

	// Lakás adatok
	int population; // Teljes népesség
	int populationInHouse; // Lakosok száma
	int homeless;  // Hajléktalanok száma
	int houseCapacity; // Lakóhelyek száma

	// Munka adatok
	int workers; // Munkások száma
	int unemployed; // Munkanélküliek száma
	int workCapacity; // Munkahelyek száma
	int industryWorkers; // Ipari munkások száma
	int serviceWorkers; // Szolgáltatás munkások száma


	GameScene* scene;
	Statistics(GameScene* gameScene);
	~Statistics();
	static Statistics* instance;

public:
	static Statistics* getInstance();
	static void createInstance(GameScene* gameScene);

	void updateStats();
};

#endif