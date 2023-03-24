#include "Window.h"

int main( int argc, char* args[] )
{
	// width, height, vsync(0 vagy 1)
	int vsync = 1;
	Window* window = new Window(600,600,vsync);
	return 0;
}