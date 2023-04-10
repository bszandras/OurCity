#pragma once
#include <vector>

#include "Resident.h"
#include "World.h"

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

	public:
		ResidentManager(World* world,Builder* builder);
		ResidentManager();

		void buildHouse(int i);
		void createResident();
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

