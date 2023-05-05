#include "Statistics.h"

Statistics* Statistics::instance = nullptr;

Statistics::Statistics(GameScene* gameScene)
{
	scene = gameScene;
}

Statistics::~Statistics()
{
	delete instance;
}

Statistics* Statistics::getInstance()
{
	instance->updateStats();
	return instance;
}

void Statistics::createInstance(GameScene* scene)
{
	if (instance == nullptr)
	{
		instance = new Statistics(scene);
	}
	else return;
}

void Statistics::updateStats()
{
	// Update the statistics
	// Population
	
	//population = scene->getResidentManager()->
}