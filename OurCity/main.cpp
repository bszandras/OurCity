#include "Window.h"

int main( int argc, char* args[] )
{
	// width, height, vsync(0 vagy 1)
	int vsync = 1;
	try
	{
		Window* window = new Window(600, 600, vsync);
	}
	catch (const std::bad_alloc& e)
	{
		std::cout << "Allocation failed: " << e.what() << '\n';
	}
	return 0;
}