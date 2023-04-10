#pragma once
#include <vector>

#include "Resident.h"
#include "World.h"

class ResidentManager {
	private:
		int factoryCount;
		int serviceCount;
		int maxEducatedUn;
		int maxEducatedHi;

		std::vector<Resident> residents;

		World* world;

	public:
		ResidentManager(World* world);
		ResidentManager();

		void updateResident();
		void handleIntention();
		int getGlobalHappiness();

		int getFactoryCount();
		int getServiceCount();
		void setFactoryCount(int x);
		void setServiceCount(int x);
		int getMaxEducatedUn();
		int getMaxEducatedHi();
};

