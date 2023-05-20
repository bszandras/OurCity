#ifdef TESTING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MyApp.h"
#include <algorithm>

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
	delete app;
}

TEST_CASE("Adding road")
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
	Tile* t2 = world->getTileOnCoords(15, 16);
	CHECK(roadGraph->addRoad(t2, state) == true);

	Tile* t3 = world->getTileOnCoords(15, 17);
	CHECK(roadGraph->addRoad(t3, state) == true);

	// Add road (check adjacency no adjacent)
	Tile* t4 = world->getTileOnCoords(20, 20);
	CHECK(roadGraph->addRoad(t4, state) == false);

	delete app;
}

TEST_CASE("Removing road")
{
	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();
	World* world = app->getScene()->getWorld();
	RoadGraph* roadGraph = world->getRoadGraph();
	GameState* state = app->getState();

	Tile* t1 = world->getTileOnCoords(15, 15);
	Tile* t2 = world->getTileOnCoords(15, 16);
	Tile* t3 = world->getTileOnCoords(15, 17);
	Tile* t4 = world->getTileOnCoords(15, 18);

	roadGraph->addRoad(t1, state);
	roadGraph->addRoad(t2, state);
	roadGraph->addRoad(t3, state);
	//CHECK(roadGraph->addRoad(t4, state) == true);


	House* h = app->getScene()->getBuilder()->BuildHouse(t3);

	// Check delete (deny)
	CHECK(roadGraph->removeRoad(t2) == false);

	// Check delete (allow)
	CHECK(roadGraph->removeRoad(t3) == true);

	// Check the function which deceides, if a building is next to a road (yes)
	CHECK(roadGraph->hasBuildingNext(t2, world->getNeighboursWritablePointers(t2)) == true);

	// Check the function which deceides, if a building is next to a road (no)
	CHECK(roadGraph->hasBuildingNext(t3, world->getNeighboursWritablePointers(t3)) == false);
	
	delete app;
}

TEST_CASE("Income and Spending")
{
	GameState *state = new GameState();

	int baseMoney = state->getMoney();

	// Add some income
	state->income(100);
	CHECK(state->getMoney() == baseMoney + 100);

	// Check if it works with negative numbers (végülis miért ne?)
	state->income(-100);
	CHECK(state->getMoney() == baseMoney);

	// Spend some money
	state->spendMoney(100);
	CHECK(state->getMoney() == baseMoney - 100);

	// Check if it works with negative numbers (végülis miért ne?)
	state->spendMoney(-100);
	CHECK(state->getMoney() == baseMoney);

	// Check if the balance can go negative
	state->spendMoney(1000000000);
	CHECK(state->getMoney() == baseMoney - 1000000000);
}

TEST_CASE("Workplace tests")
{
	Tile* t1 = new Tile();

	std::vector<Resident*> residents;
	for (int i = 0; i < 10; i++)
	{
		Resident* r = new Resident();
		residents.push_back(r);
	}

	Workplace* wp = new Workplace(t1);


	// Kapacitás átállításának tesztelése
	wp->setCapacity(2);
	CHECK(wp->getCapacity() == 2);

	// Munkások hozzáadása
	CHECK(wp->canWorkHere() == true);
	wp->addWorker(0);
	CHECK(wp->getWorkers().size() == 1);

	CHECK(wp->canWorkHere() == true);
	wp->addWorker(1);
	CHECK(wp->getWorkers().size() == 2);

	// Megnézzük, hogy ha tele van a munkahely, akkor nem lehet több munkást hozzáadni
	CHECK(wp->canWorkHere() == false);

	// Munkások törlése
	wp->removeWorker(0);
	CHECK(wp->getWorkers().size() == 1);

	wp->removeWorker(1);
	CHECK(wp->getWorkers().size() == 0);


	// Összes munkás törlésének tesztelése
	wp->addWorker(0);
	wp->addWorker(1);
	wp->clearWorkers();
	CHECK(wp->getWorkers().size() == 0);

}
#endif