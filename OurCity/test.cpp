#ifdef TESTING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MyApp.h"


TEST_CASE("1 is equal to 1", "[equality]")
{
	REQUIRE(1 == 1);
}

TEST_CASE("Road test")
{
	CMyApp* app = new CMyApp();
	app->Init();
	app->Update();
	World* world = app->getScene()->getWorld();
	Tile* t1 = world->getTileOnCoords(50, 50);
	CHECK(world->AddRoad(t1, app->getScene()) == true);
}


#endif