#ifndef STATISTICS_H
#define STATISTICS_H

#include "GameScene.h"

class Statistics
{
private:
	// Statisztikai adatok

	// Lak�s adatok
	int population; // Teljes n�pess�g
	int populationInHouse; // Lakosok sz�ma
	int homeless;  // Hajl�ktalanok sz�ma
	int houseCapacity; // Lak�helyek sz�ma

	// Munka adatok
	int workers; // Munk�sok sz�ma
	int unemployed; // Munkan�lk�liek sz�ma
	int workCapacity; // Munkahelyek sz�ma
	int industryWorkers; // Ipari munk�sok sz�ma
	int serviceWorkers; // Szolg�ltat�s munk�sok sz�ma


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