#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#ifndef TESTING
#include <crtdbg.h>
#include "Window.h"
#endif

#ifdef TESTING
#include "MyApp.h"
#endif

int main( int argc, char* args[] )
{
#ifdef TESTING
	std::clog << "[INFO] Application is running in test mode" << std::endl;
#else
	std::clog << "[INFO] Application is running in normal mode" << std::endl;
#endif
	// width, height, vsync(0 vagy 1)

#ifdef TESTING
	CMyApp* app = new CMyApp();

#else
	int vsync = 1;

	Window* window = new Window(800, 800, vsync);

	delete window;
#endif

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
	return 0;
}