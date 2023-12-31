#ifndef STATISTICS_H
#define STATISTICS_H

#include "GameScene.h"

class Statistics
{
private:
	// �ltal�nos v�ros statisztika
	int population; // Teljes n�pess�g
	float avgAge; // �tlag �letkor
	int money; // P�nz
	float avgHappiness; // �tlagos boldogs�g
	int pensionerCount; // Nyugd�jasok sz�ma
	float avgPension; // �tlagnyugd�j

	// Lak�s adatok
	int homeless;  // Hajl�ktalanok sz�ma
	int populationInHouse; // Lakosok sz�ma
	int houseCapacity; // Lak�helyek sz�ma
	int houseCapacityFree; // Szabad lak�helyek sz�ma
	float houseCapacityPercent; // Lak�helyek kihaszn�lts�ga

	// Munka adatok
	int workers; // Munk�sok sz�ma
	int unemployed; // Munkan�lk�liek sz�ma
	int workCapacity; // Munkahelyek sz�ma
	int factoryCapacity; // Gy�rak kapacit�sa
	int serviceCapacity; // Szolg�ltat�s kapacit�sa
	int industryWorkers; // Ipari munk�sok sz�ma
	int serviceWorkers; // Szolg�ltat�s munk�sok sz�ma
	float workingPercentage; // Munkav�llal�s ar�nya
	float serviceIndustryBalance; // Ipar-szolg�ltat�s munk�sok balansz ar�nya (Ha >100, akkor t�bb a szolg�ltat�si munk�s, ha <100, akkor a gy�ri munk�s t�bb

	// Oktat�si adatok
	int highSchoolEducated; // K�z�piskolai oktat�sban r�szes�l
	int universityEducated; // Egyetemi oktat�sban r�szes�lt
	int uneducated; // Tanulatlanok sz�ma
	int educated; // Tanultak sz�ma
	int educationPercentage; // Tanultak ar�nya


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

	// Getterek az �sszes adattaghoz
	int getPopulation();
	float getAvgAge();
	int getMoney();
	float getAvgHappiness();
	int getPensionerCount();
	float getAvgPension();
	int getHomeless();
	int getPopulationInHouse();
	int getHouseCapacity();
	int getHouseCapacityFree();
	float getHouseCapacityPercent();
	int getWorkers();
	int getUnemployed();
	int getWorkCapacity();
	int getFactoryCapacity();
	int getServiceCapacity();
	int getIndustryWorkers();
	int getServiceWorkers();
	float getWorkingPercentage();
	float getServiceIndustryBalance();
	int getHighSchoolEducated();
	int getUniversityEducated();
	int getUneducated();
	int getEducated();
	int getEducationPercentage();

};

#endif