#pragma once
#include <vector>

// GLEW
#include <GL/glew.h>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>

#include "GameScene.h"
#include "MouseController.h"
#include "AppTime.h"
#include "Builder.h"

class CMyApp
{
public:
	CMyApp(void);
	~CMyApp(void);

	bool Init();
	void Clean();

	void Update();
	void Render();

	void KeyboardDown(SDL_KeyboardEvent&);
	void KeyboardUp(SDL_KeyboardEvent&);
	void MouseMove(SDL_MouseMotionEvent&);
	void MouseDown(SDL_MouseButtonEvent&);
	void MouseUp(SDL_MouseButtonEvent&);
	void MouseWheel(SDL_MouseWheelEvent&);
	void Resize(int, int);
	//ez átmozog másik osztályba
	void LoadTextures();

	void ChangeBuilderState(BuilderState state, BuilderSubState subState);
	void ChangeSpeed(int i);
protected:
	// shaderekhez szükséges változók
	GLuint m_programID; // shaderek programja

	// OpenGL-es dolgok
	GLuint m_vaoID; // vertex array object erőforrás azonosító
	GLuint m_vboID; // vertex buffer object erőforrás azonosító

	//shader adatok
	GLuint camDataUniformLoc;
	GLuint winDataUniformLoc;

	GLuint textureArrayLoc;

	int vertCount = 0;
	
	//input
	std::vector<int> currentlyPressedKeys;

	struct Vertex
	{
		glm::vec3 p;
		glm::vec3 c;
	};

	GameScene* scene;
	MouseController* mouseController;
	Time* time;
	//Builder* builder;
};

