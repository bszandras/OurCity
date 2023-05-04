#ifdef TESTING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MyApp.h"


TEST_CASE("Testing tester functionality", "[tester]")
{
	REQUIRE(1 == 1);
}

TEST_CASE("Application initalization tests", "[appInit]")
{
	CMyApp* app = new CMyApp();
	CHECK(app->Init() == true);
	CHECK(app->getScene() != nullptr);
	CHECK(app->getState() != nullptr);
}

TEST_CASE("RoadGraph test")
{
	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();
	World* world = app->getScene()->getWorld();
	RoadGraph* roadGraph = world->getRoadGraph();
	GameState* state = app->getState();

	// Add first road
	Tile* t1 = world->getTileOnCoords(15, 15);
	CHECK(roadGraph->addRoad(t1, state) == true);

	// Add some road (check adjacency, allow)
	Tile* t2 = world->getTileOnCoords(15,16);
	CHECK(roadGraph->addRoad(t2, state) == true);

	Tile* t3 = world->getTileOnCoords(15, 17);
	CHECK(roadGraph->addRoad(t3, state) == true);

	// Add road (check adjacency no adjacent)
	Tile* t4 = world->getTileOnCoords(20,20);
	CHECK(roadGraph->addRoad(t4, state) == false);

	// Check delete (deny)
	CHECK(roadGraph->removeRoad(t2) == false);

	// Check delete (allow)
	CHECK(roadGraph->removeRoad(t3) == true);
}


#endif