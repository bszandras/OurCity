#include "Tester.h"

void Tester::runRoadTests()
{
	World* world = app->getScene()->getWorld();
	Tile* t1 = world->getTileOnCoords(50, 50);

	std::clog << "[TESTER] Running road tests" << std::endl;
	CHECK(world->AddRoad(t1, app->getScene()) == true);
	std::clog << "[TESTER] Road tests finished" << std::endl;
}

Tester::Tester(CMyApp* app)
{
	this->app = app;
}

Tester::~Tester()
{
}

void Tester::runTests()
{

	runRoadTests();
}
