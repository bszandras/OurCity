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

TEST_CASE("Building tests")
{
	// build spec buildings
	// test if buildings are there

	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();

	World* world = app->getScene()->getWorld();
	RoadGraph* roadGraph = world->getRoadGraph();
	GameState* state = app->getState();
	Builder* builder = app->getScene()->getBuilder();

	Tile* t1 = world->getTileOnCoords(15, 15);
	int t1ID = 15 * world->getWidth() + 15;
	builder->ChangeState(BUILDING, ROAD);
	builder->Build(t1ID);
	//roadGraph->addRoad(t1, state);

	Tile* t2 = world->getTileOnCoords(15, 16);
	int t2ID = 16 * world->getWidth() + 15;

	// set building intention
	builder->ChangeState(BUILDING, FIRESTATION);
	builder->Build(t2ID);

	// check if firestation has been built
	Building* building = t2->building;
	FireStation* firestation = (FireStation*)building;
	CHECK(firestation != nullptr);
	CHECK(world->getFireStations()->size() > 0);

	// build stadium
	Tile* t3 = world->getTileOnCoords(14, 16);
	int t3ID = 16 * world->getWidth() + 14;
	builder->ChangeState(BUILDING, STADIUM);
	builder->Build(t3ID);

	// check stadium
	building = t3->building;
	Stadium* stadium = (Stadium*)building;
	CHECK(stadium != nullptr);

	// build highschool
	Tile* t4 = world->getTileOnCoords(15, 13);
	int t4ID = 13 * world->getWidth() + 15;
	builder->ChangeState(BUILDING, HIGHSCHOOL);
	builder->Build(t4ID);

	// check stadium
	building = t4->building;
	HighSchool* highschool = (HighSchool*)building;
	CHECK(highschool != nullptr);
	CHECK(world->getHighSchools()->size() == 1);


	// CHECK TEXTURE UPDATES
	CHECK(t1->texId == ROAD);
	CHECK(t2->texId == FIRESTATION);
	CHECK(t3->texId == STADIUM);
	CHECK(t4->texId == HIGHSCHOOL);

	// -----------
	// DEMOLISH
	// -----------

	builder->ChangeState(BUILDINGDESTROY, NONE);
	builder->Build(t2ID);
	CHECK(t2->building == nullptr);

	builder->Build(t3ID);
	CHECK(t3->building == nullptr);

	builder->Build(t4ID);
	CHECK(t4->building == nullptr);

	// CHECK TEXTURE UPDATES
	CHECK(t2->texId == 2);
	CHECK(t3->texId == 2);
	CHECK(t4->texId == 2);

	delete app;
}
TEST_CASE("Tax setting tests")
{
	// change tax settings
	// check if tax settings changed

	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();

	World* world = app->getScene()->getWorld();
	RoadGraph* roadGraph = world->getRoadGraph();
	GameState* state = app->getState();


	// GLOBAL TAX SETTING
	float oldTax = world->getGlobalTaxRate();
	float* taxHandle = world->getGlobalTaxRateHandle();
	*taxHandle = 1.1;
	float newTax = world->getGlobalTaxRate();

	CHECK(oldTax < newTax);
	CHECK(newTax == 1.1f);

	// HOUSING TAX SETTING
	oldTax = world->getHousingTaxRate();
	taxHandle = world->getHousingTaxRateHandle();
	*taxHandle = 1.2;
	newTax = world->getHousingTaxRate();

	CHECK(oldTax < newTax);
	CHECK(newTax == 1.2f);

	// INDUSTRY TAX SETTING
	oldTax = world->getIndustrialTaxRate();
	taxHandle = world->getIndustrialTaxRateHandle();
	*taxHandle = 1.3;
	newTax = world->getIndustrialTaxRate();

	CHECK(oldTax < newTax);
	CHECK(newTax == 1.3f);

	// SERVICE TAX SETTING
	oldTax = world->getServiceTaxRate();
	taxHandle = world->getServiceTaxRateHandle();
	*taxHandle = 1.4;
	newTax = world->getServiceTaxRate();

	CHECK(oldTax < newTax);
	CHECK(newTax == 1.4f);

	delete app;

}
TEST_CASE("Creating residents int the manager test")
{
	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();
	ResidentManager* residentManager = app->getScene()->getResidentManager();

	//There are 3 residents when the game starts
	int resSize = residentManager->getResSize();

	CHECK(resSize == 3);

	//5 more residents -> 8 in total
	for (int i = 0; i < 5; i++)
	{
		residentManager->createResident();
	}
	resSize = residentManager->getResSize();
	CHECK(resSize == 8);

	//They are all homeless
	int homeless = residentManager->getHomeless();

	CHECK(homeless == 8);

	float averageAge = residentManager->getAverageAge();

	//All residents are 18
	CHECK(averageAge == 18);

	//A year has passed
	residentManager->updateResidentYearly();

	averageAge = residentManager->getAverageAge();

	CHECK(averageAge == 19);

	delete app;

}
TEST_CASE("Maintenance cost")
{
	GameState* state = new GameState();

	int sumMaintenance = state->getSumMaintenance();

	CHECK(sumMaintenance == 0);

	state->addToMaintenance(10);

	CHECK(state->getSumMaintenance() == 10);

	state->addToMaintenance(100);

	state->subFromMaintenance(10);

	CHECK(state->getSumMaintenance() == 100);

}
TEST_CASE("Game Over")
{
	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();
	ResidentManager* residentManager = app->getScene()->getResidentManager();
	World* world = app->getScene()->getWorld();
	GameState* state = app->getState();
	GameScene* scene = app->getScene();

	*world->getGlobalTaxRateHandle() = 1.5f;
	*world->getHousingTaxRateHandle() = 1.5f;
	*world->getIndustrialTaxRateHandle() = 1.5f;
	*world->getServiceTaxRateHandle() = 1.5f;

	residentManager->updateGlobalHappiness();
	residentManager->calculateGlobalHappiness();
	residentManager->updateResidentYearly();
	scene->isGameOver();
	residentManager->updateResidentYearly();
	scene->isGameOver();
	residentManager->updateResidentYearly();
	scene->isGameOver();
	CHECK(scene->getGameOver() == true);

	delete app;
}
#endif