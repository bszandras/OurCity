#pragma once
#include <vector>

#include "Resident.h"

class ResidentManager {
	private:
		int factoryCount;
		int serviceCount;
		int maxEducatedUn;
		int maxEducatedHi;

		std::vector<Resident> residents;

	public:
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

