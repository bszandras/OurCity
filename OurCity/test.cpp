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

TEST_CASE("Road test")
{
	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();
	World* world = app->getScene()->getWorld();

	Tile* t1 = world->getTileOnCoords(15, 15);
	CHECK(world->AddRoad(t1, app->getScene()) == true);
}


#endif