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
#ifndef TESTING
	std::clog << "[INFO] Application is running in normal mode" << std::endl;
	// width, height, vsync(0 vagy 1)



	int vsync = 1;

	Window* window = new Window(800, 800, vsync);

	delete window;

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
#endif
#ifdef TESTING
	std::clog << "[INFO] Application is running in test mode" << std::endl;
	CMyApp *app = new CMyApp();
	app->Init();
	app->Update();
	delete app;
#endif

	return 0;
}