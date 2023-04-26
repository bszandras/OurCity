#pragma once
#include <vector>

#include "Resident.h"
#include "World.h"
#include "GamesTate.h"

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

		void buildHouse(int i);
		void createResident();
		void updateResidentYearly();
		void updateResidentMonthly();
		void handleIntention();
		void buildFactory(int i);
		void buildService(int i);
		float getGlobalHappiness();

		int residentMoveIn();
		void updateGlobalHappiness();
		void updateResident(Resident* resident);
		void recalculateResidentTax();

		void loseHouse(int hosueID);
		void loseJobFactory(int jobID);
		void loseJobService(int jobID);

		int calculateHappiness();

		int getFactoryCount();
		int getServiceCount();
		void setFactoryCount(int x);
		void setServiceCount(int x);
		int getMaxEducatedUn();
		int getMaxEducatedHi();
};

