#pragma once
#include <vector>

#include "Resident.h"
#include "World.h"
#include "GameState.h"

class Builder;
class World;
class ResidentManager {
	private:
		int factoryCount;
		int serviceCount;

		int maxEducatedUn;
		int maxEducatedHi;

		float globalHappiness;

		std::vector<Resident> residents;

		World* world;
		Builder* builder;
		GameState* gameState;

		void calculateHousingTax();
		void calculateIndustrialTax();
		void calculateServiceTax();

	public:
		ResidentManager(World* world,Builder* builder, GameState* gameState);
		ResidentManager();

		void createResident();
		void updateResidentYearly();
		void updateResidentMonthly();

		void handleIntention();
		void buildHouse(int i);
		void buildFactory(int i);
		void buildService(int i);
		int residentMoveIn();

		void loseHouse(int hosueID);
		void loseJobFactory(int jobID);
		void loseJobService(int jobID);
		void residentDeath();
		void residentMove();

		void updateGlobalHappiness();
		void recalculateResidentTax();
		void calculateHappiness(Resident* res);
		void calculateGlobalHappiness();

		void setFactoryCount(int x);
		void setServiceCount(int x);

		std::vector<Resident> getResidents();
		Resident* getResident(int id);
		int getResSize();
		int getResidentCount() const;
		float getGlobalHappiness();
		float getAverageAge() const;
		int getHomeless() const;
		int getFactoryCount();
		int getServiceCount();
		int getMaxEducatedUn();
		int getMaxEducatedHi();

};

