#ifndef STATISTICS_H
#define STATISTICS_H

#include "GameScene.h"

class Statistics
{
private:
	// Statisztikai adatok

	// Általános város statisztika
	int population; // Teljes népesség
	float avgAge; // Átlag életkor
	int money; // Pénz
	float avgHappiness; // Átlagos boldogság

	// Lakás adatok
	int homeless;  // Hajléktalanok száma
	int populationInHouse; // Lakosok száma
	int houseCapacity; // Lakóhelyek száma
	int houseCapacityFree; // Szabad lakóhelyek száma
	float houseCapacityPercent; // Lakóhelyek kihasználtsága

	// Munka adatok
	int workers; // Munkások száma
	int unemployed; // Munkanélküliek száma
	int workCapacity; // Munkahelyek száma
	int factoryCapacity; // Gyárak kapacitása
	int serviceCapacity; // Szolgáltatás kapacitása
	int industryWorkers; // Ipari munkások száma
	int serviceWorkers; // Szolgáltatás munkások száma
	float workingPercentage; // Munkavállalás aránya
	float serviceIndustryBalance; // Ipar-szolgáltatás munkások balansz aránya (Ha >100, akkor több a szolgáltatási munkás, ha <100, akkor a gyári munkás több

	// Oktatási adatok
	int highSchoolEducated; // Középiskolai oktatásban részesül
	int universityEducated; // Egyetemi oktatásban részesült
	int uneducated; // Tanulatlanok száma
	int educated; // Tanultak száma
	int educationPercentage; // Tanultak aránya


	GameScene* scene;
	Statistics(GameScene* gameScene);
	~Statistics();
	static Statistics* instance;

	void updateGeneralStatistics();
	void updateHousingStatistics();
	void updateWorkingStatistics();
	void updateEducateStatistics();

public:
	static Statistics* getInstance();
	static void createInstance(GameScene* gameScene);

	void updateStats();

};

#endif