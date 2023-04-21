#pragma once

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MyApp.h"

class Tester
{
private:
	CMyApp* app;

	void runRoadTests();

public:
	Tester(CMyApp* app);
	~Tester();

	void runTests();
};

