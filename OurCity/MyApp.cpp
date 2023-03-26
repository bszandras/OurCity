#include <iostream>
#include <vector>
#include <math.h>

#include "MyApp.h"

#include <SDL.h>
#include <SDL_image.h>
#include "GLUtils.hpp"

#include "TileRect.h"
#include "World.h"
#include "Camera.h"
#include "Window.h"


CMyApp::CMyApp(void)
{
	m_vaoID = 0;
	m_vboID = 0;
	m_programID = 0;
	camDataUniformLoc = 0;
	winDataUniformLoc = 0;
	textureArrayLoc = 0;
}


CMyApp::~CMyApp(void)
{
}

bool CMyApp::Init()
{
	// törlési szín legyen kékes
	glClearColor(0.125f, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE); // kapcsoljuk be a hátrafelé néző lapok eldobását
	glEnable(GL_DEPTH_TEST); // mélységi teszt bekapcsolása (takarás)
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//
	// geometria létrehozása
	//

	scene = new GameScene();

	// 1 db VAO foglalása
	glGenVertexArrays(1, &m_vaoID);
	// a frissen generált VAO beállítasa aktívnak
	glBindVertexArray(m_vaoID);
	
	// hozzunk létre egy új VBO erőforrás nevet
	glGenBuffers(1, &m_vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	/*
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // tegyük "aktívvá" a létrehozott VBO-t
	// töltsük fel adatokkal az aktív VBO-t
	glBufferData( GL_ARRAY_BUFFER,					// az aktív VBO-ba töltsünk adatokat
				  sizeof(Vertex) * vertCount,		// ennyi bájt nagyságban
				  vert,								// erről a rendszermemóriabeli címről olvasva
				  GL_STATIC_DRAW);					// úgy, hogy a VBO-nkba nem tervezünk ezután írni és minden kirajzoláskor felhasnzáljuk a benne lévő adatokat	
				  */
	// VAO-ban jegyezzük fel, hogy a VBO-ban az első 3 float sizeof(Vertex)-enként lesz az első attribútum (pozíció)
	glEnableVertexAttribArray(0); // ez lesz majd a pozíció
	glVertexAttribPointer(
		(GLuint)0,				// a VB-ben található adatok közül a 0. "indexű" attribútumait állítjuk be
		3,				// komponens szám
		GL_FLOAT,		// adatok típusa
		GL_FALSE,		// normalizált legyen-e
		sizeof(Vertex),	// stride (0=egymás után)
		0				// a 0. indexű attribútum hol kezdődik a sizeof(Vertex)-nyi területen belül
	); 

	// a második attribútumhoz pedig a VBO-ban sizeof(Vertex) ugrás után sizeof(glm::vec3)-nyit menve újabb 3 float adatot találunk (szín)
	glEnableVertexAttribArray(1); // ez lesz majd a szín
	glVertexAttribPointer(
		(GLuint)1,
		3, 
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(void*)(sizeof(glm::vec3)) );

	glBindVertexArray(0); // feltöltüttük a VAO-t, kapcsoljuk le
	glBindBuffer(GL_ARRAY_BUFFER, 0); // feltöltöttük a VBO-t is, ezt is vegyük le

	//
	// shaderek betöltése
	//
	GLuint vs_ID = loadShader(GL_VERTEX_SHADER,		"myVert.vert");
	GLuint fs_ID = loadShader(GL_FRAGMENT_SHADER,	"myFrag.frag");

	// a shadereket tároló program létrehozása
	m_programID = glCreateProgram();

	// adjuk hozzá a programhoz a shadereket
	glAttachShader(m_programID, vs_ID);
	glAttachShader(m_programID, fs_ID);

	// attributomok osszerendelese a VAO es shader kozt
	glBindAttribLocation( m_programID, 0, "vs_in_pos");
	glBindAttribLocation( m_programID, 1, "vs_in_col");

	// illesszük össze a shadereket (kimenő-bemenő változók összerendelése stb.)
	glLinkProgram(m_programID);

	// linkelés ellenőrzese
	GLint infoLogLength = 0, result = 0;

	glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (GL_FALSE == result || infoLogLength != 0)
	{
		std::vector<char> VertexShaderErrorMessage(infoLogLength);
		glGetProgramInfoLog(m_programID, infoLogLength, nullptr, VertexShaderErrorMessage.data());

		std::cerr << "[glLinkProgram] Shader linking error:\n" << &VertexShaderErrorMessage[0] << std::endl;
	}

	// már nincs ezekre szükség
	glDeleteShader( vs_ID );
	glDeleteShader( fs_ID );

	glUseProgram(m_programID);
	camDataUniformLoc = glGetUniformLocation(m_programID, "camData");
	winDataUniformLoc = glGetUniformLocation(m_programID, "windowSize");
	textureArrayLoc = glGetUniformLocation(m_programID, "textureAtlas");

	LoadTextures();

	glUseProgram(0);

	return true;
}

void CMyApp::Clean()
{
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);

	glDeleteProgram( m_programID );
}

void CMyApp::Update()
{
	World* world = scene->getWorld();
	if (currentlyPressedKeys.size() != 0)
	{
		//input handling és camera cuccok
		Vector2Data camDir = { 0.0f,0.0f };
		for (int i = 0; i < currentlyPressedKeys.size(); i++)
		{

			switch (currentlyPressedKeys[i])
			{
			case(SDL_KeyCode::SDLK_w):
				camDir.y += 1.0f;
				break;
			case(SDL_KeyCode::SDLK_a):
				camDir.x -= 1.0f;
				break;
			case(SDL_KeyCode::SDLK_s):
				camDir.y -= 1.0f;
				break;
			case(SDL_KeyCode::SDLK_d):
				camDir.x += 1.0f;
				break;
			case(SDL_KeyCode::SDLK_k):
				scene->getCamera()->Zoom(0.1f);
				break;
			case(SDL_KeyCode::SDLK_l):
				scene->getCamera()->Zoom(-0.1f);
				break;
			default:
				break;
			}
		}
		scene->getCamera()->Move(camDir);
	}
	
	// DEMO egér input
	Vector2Data worldPos = Vector2Tool::ScreenToWorldSpace({ mousePosition.x,mousePosition.y }, 
		{ (float)Window::instance->getWidth(), (float)Window::instance->getHeight() }, 
		scene->getCamera()->getPosition(), scene->getCamera()->getZoom(), 
		world->getOrigoOffset());

	Vector2Data tileId = world->tileCoorOnWorldPosition(worldPos);
	if (tileId.x < 0 || tileId.y < 0 || tileId.x > world->getWidth() - 1 || tileId.y > world->getHeight() - 1)
	{
		return;
	}
	world->getWrapper()->UpdateTexIdById((tileId.y * world->getWidth() + tileId.x), 1);

	movedMouseThisFrame = false;
}

void CMyApp::Render()
{
	// töröljük a frampuffert (GL_COLOR_BUFFER_BIT) és a mélységi Z puffert (GL_DEPTH_BUFFER_BIT)
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cullcheck és vertex data konstruálás

	World* world = scene->getWorld();
	Camera* camera = scene->getCamera();

	Vertex* vert;
	std::vector<SubMap>* subs = world->getSubmaps();

	std::vector<Vector3Data> rects;
	int c = 0;
	for (int i = 0; i < subs->size(); i++)
	{
		if (subs->at(i).shouldBeCulled(camera))
		{
			continue;
		}
		c++;
		Vector3Data* d = subs->at(i).getRectData(world->getWrapper());
		for (int j = 0; j < subs->at(i).getRectCount(); j++)
		{
			//hatalmas bottleneck
			rects.push_back(d[j]);
		}
		delete d;
	}
	vert = new Vertex[(rects.size()) * 4];
	int worldHeight = world->getHeight();
	for (int i = 0; i < rects.size(); i++)
	{
		//ide kell még a world->screen->shader konv
		//lehet mehet shaderbe
		//ha a shader megkapja a kamera adatokat és a képernyő aktuális méretét
		//akkor a vertexshader képes szortírozni, és nem kell frame-enként rekonstruálni a buffert

		Vector3Data currRect = rects[i];
		//rect y-jából tudok z-depth-et számolni, betolom egy -0.9 - 0.9 space-be
		//rect.z-ben alapból texid van
		float rectDepth = currRect.y / 64 / worldHeight;	//[0,1]
		//rectDepth *= 1.9f;									//[0,1.8]
		//rectDepth -= 0.9f;									//[-0.9, 0.9]
		rectDepth *= 0.9f;
		//ezek valamiért sok cpu időbe kerülnek
		//azért furcsa, mert a memória terület már le van foglalva, csak fel kell tölteni adattal
		//valamiért az indexelés rettenet drága
		//prolly nem az i*4+valamennyi, mert az 1 órajel alatt megvan FMA-val
		vert[i * 4] = { glm::vec3(currRect.x, currRect.y, rectDepth), glm::vec3(0, 1, currRect.z) };
		vert[i * 4 + 1] = { glm::vec3((currRect.x + 64), currRect.y, rectDepth), glm::vec3(1, 1, currRect.z) };
		vert[i * 4 + 2] = { glm::vec3((currRect.x + 64), (currRect.y + 64), rectDepth), glm::vec3(1, 0, currRect.z) };
		vert[i * 4 + 3] = { glm::vec3(currRect.x, (currRect.y + 64), rectDepth), glm::vec3(0, 0, currRect.z) };
	}

	vertCount = (rects.size()) * 4;

	// hozzunk létre egy új VBO erőforrás nevet
	//glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID); // tegyük "aktívvá" a létrehozott VBO-t
	// töltsük fel adatokkal az aktív VBO-t
	glBufferData(GL_ARRAY_BUFFER,					// az aktív VBO-ba töltsünk adatokat
		sizeof(Vertex) * vertCount,		// ennyi bájt nagyságban
		vert,								// erről a rendszermemóriabeli címről olvasva
		//GL_STATIC_DRAW);					// úgy, hogy a VBO-nkba nem tervezünk ezután írni és minden kirajzoláskor felhasnzáljuk a benne lévő adatokat	
		GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] vert;

	// shader bekapcsolása, ebben a projektben a teljes programot jelöli, hisz nem váltunk a shaderek között
	glUseProgram( m_programID );

	// kapcsoljuk be a VAO-t (a VBO jön vele együtt)
	glBindVertexArray(m_vaoID);

	// shadernek átdobjuk a kamera és ablak adatokat
	Vector2Data cpos = camera->getPosition();
	glm::vec3 cam = { cpos.x,cpos.y,camera->getZoom() };
	glm::vec2 window = { Window::instance->getWidth(),Window::instance->getHeight() };

	glUniform3f(camDataUniformLoc, cam.x, cam.y, cam.z);
	glUniform2f(winDataUniformLoc, window.x, window.y);

	// kirajzolás
	//A draw hívásokhoz a VAO és a program bindolva kell legyenek (glUseProgram() és glBindVertexArray())
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_QUADS, 0, vertCount);

	// VAO kikapcsolása
	glBindVertexArray(0);

	// shader kikapcsolása
	glUseProgram( 0 );
}

void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	//ha üres a lista, akkor nem kell ellenőrizni, hogy benne van-e
	if (currentlyPressedKeys.size() == 0)
	{
		currentlyPressedKeys.push_back(key.keysym.sym);
		return;
	}
	//check hogy benne van-e
	for (int i = 0; i < currentlyPressedKeys.size(); i++)
	{
		if (currentlyPressedKeys[i] == key.keysym.sym)
		{
			return;
		}
	}
	currentlyPressedKeys.push_back(key.keysym.sym);
}

void CMyApp::KeyboardUp(SDL_KeyboardEvent& key)
{
	if (currentlyPressedKeys.size() == 0)
	{
		return;
	}
	for (int i = 0; i < currentlyPressedKeys.size(); i++)
	{
		if (currentlyPressedKeys[i] == key.keysym.sym)
		{
			currentlyPressedKeys.erase(currentlyPressedKeys.begin() + i);
			return;
		}
	}
	
}

void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
	/*
	if (movedMouseThisFrame)
	{
		return;
	}
	*/
	movedMouseThisFrame = true;
	mousePosition = { (float)mouse.x, (float)mouse.y };
}

void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
}

void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}

// a két paraméterben az új ablakméret szélessége (_w) és magassága (_h) található
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );
	//ez fontos
	scene->getWorld()->reCalculateOrigoOffset();
}

void CMyApp::LoadTextures()
{
	GLuint texture;
	SDL_Surface* surface;
	surface = IMG_Load("textureatlas.png");
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glUniform1i(textureArrayLoc, 0);

	SDL_FreeSurface(surface);
}