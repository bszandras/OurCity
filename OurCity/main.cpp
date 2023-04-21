#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#ifndef TESTING
#include <crtdbg.h>
#include "Window.h"
#endif

#ifdef TESTING
#include "MyApp.h"
#include "Tester.h"
#endif

#ifndef TESTING
int main( int argc, char* args[] )
{
	std::clog << "[INFO] Application is running in normal mode" << std::endl;
	// width, height, vsync(0 vagy 1)



	int vsync = 1;

	Window* window = new Window(800, 800, vsync);

	delete window;

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
	return 0;
}
#endif

#ifdef TESTING
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testing the tester", "[tester]")
{
	CHECK(1 == 1);
}
#endif