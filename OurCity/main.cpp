#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

// memory leak
#include <crtdbg.h>

#include "Window.h"

int main( int argc, char* args[] )
{
	// width, height, vsync(0 vagy 1)
	int vsync = 1;

	Window* window = new Window(800, 800, vsync);

	delete window;

	//_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	//_CrtDumpMemoryLeaks();
	return 0;
}