#pragma once

#ifndef TESTING

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// standard
#include <iostream>
#include <sstream>

#include "GLDebugMessageCallback.h" 

// custom
#include "MyApp.h"

class Window
{
private:
	int width;
	int height;
	int swapIntervall;
	SDL_Event event;
	CMyApp* app;
	SDL_Window* win;
	SDL_GLContext context;

	int SDLInit();
	int StartGameLoop();
	int HandleEvents(bool& quit, SDL_Event ev);
public:
	static Window* instance;
	Window(int w, int h, int swap);
	~Window();
	int getWidth();
	int getHeight();
};

#endif