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

		std::vector<Resident> residents;

		World* world;
		Builder* builder;
		GameState* gameState;
		

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
		int getGlobalHappiness();
		void updateResident(Resident* resident);
		void recalculateResidentTax();

		int calculateHappiness();

		int getFactoryCount();
		int getServiceCount();
		void setFactoryCount(int x);
		void setServiceCount(int x);
		int getMaxEducatedUn();
		int getMaxEducatedHi();
};

