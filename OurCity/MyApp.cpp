#include <iostream>
#include <vector>
#include <math.h>
//#include <algorithm>

#include "MyApp.h"

#ifndef TESTING
#include <SDL.h>
#include <SDL_image.h>
#include "GLUtils.hpp"
#include "Camera.h"
#include "Window.h"
#endif

#include "TileRect.h"
#include "World.h"

#include "BuildingsInclude.h"
#include "RoadGraph.h"
#include "Helicopter.h"


/// <summary>
/// Szimuláció konstruktora
/// </summary>
/// <param name=""></param>
/// <returns></returns>
CMyApp::CMyApp(void)
{
#ifndef TESTING
	m_vaoID = 0;
	m_vboID = 0;
	overlay_vaoID = 0;
	overlay_vboID = 0;

	m_programID = 0;
	camDataUniformLoc = 0;
	winDataUniformLoc = 0;
	textureArrayLoc = 0;
#endif
}


CMyApp::~CMyApp(void)
{
#ifndef TESTING
	delete mouseController;
#endif
	delete scene;
	delete time;
}

/// <summary>
/// Ez inicializál mindent, a szimulációs logikát és a rendereléshez szükséges erőforrásokat is.
/// </summary>
/// <returns>Igazzal tér vissza ha sikeres az inicializáció.</returns>
bool CMyApp::Init()
{
#ifndef TESTING
	// törlési szín legyen kékes
	glClearColor(1, 0.25f, 0.5f, 1.0f);

	glEnable(GL_CULL_FACE); // kapcsoljuk be a hátrafelé néző lapok eldobását
	glEnable(GL_DEPTH_TEST); // mélységi teszt bekapcsolása (takarás)
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//
	// geometria létrehozása
	//
	mouseController = new MouseController();
#endif

#ifdef TESTING
	scene = new GameScene(nullptr);
	time = new Time(1000 / 1000.0f);
#else
	time = new Time(SDL_GetTicks() / 1000.0f);
	scene = new GameScene(mouseController);
	overlay = new Overlay();
#endif

#ifndef TESTING

	// ----------
	// NORMÁL VAO
	// ----------

	// 1 db VAO foglalása
	glGenVertexArrays(1, &m_vaoID);
	// a frissen generált VAO beállítasa aktívnak
	glBindVertexArray(m_vaoID);
	
	// hozzunk létre egy új VBO erőforrás nevet
	glGenBuffers(1, &m_vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	
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


	// ----------
	// OVERLAY VAO
	// ----------

	// 1 db VAO foglalása
	glGenVertexArrays(1, &overlay_vaoID);
	// a frissen generált VAO beállítasa aktívnak
	glBindVertexArray(overlay_vaoID);

	// hozzunk létre egy új VBO erőforrás nevet
	glGenBuffers(1, &overlay_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, overlay_vboID);

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
		(void*)(sizeof(glm::vec3)));

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
	lightMaskLoc = glGetUniformLocation(m_programID, "lightMask");
	timeCycleLoc = glGetUniformLocation(m_programID, "time_cycle");

	LoadTextures();

	glUseProgram(0);
#endif
	return true;
}

/// <summary>
/// Felszabadítja a renderelésnél felhasznált erőforrásokat.
/// </summary>
void CMyApp::Clean()
{
#ifndef TESTING
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);

	glDeleteBuffers(1, &overlay_vboID);
	glDeleteVertexArrays(1, &overlay_vaoID);

	glDeleteProgram( m_programID );
#endif
}

/// <summary>
/// Játék update tick-je.
/// Ebben fut a szimuláció és ez kezeli a felhasználói inputot.
/// </summary>
void CMyApp::Update()
{
	// frame elején inicializáljuk az aktuális időt
	// deltaTime így Update + Render alatt eltellt idő lesz
#ifdef TESTING
	time->UpdateTime(1000 / 1000.0f);
	scene->update();
#else
	time->UpdateTime(SDL_GetTicks() / 1000.0f);
	scene->update();
	//std::cout << time->getDelta() << std::endl;
#endif

	World* world = scene->getWorld();

#ifndef TESTING
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
	if (mouseController->getMouseState() != MouseState::NOTHING)
	{
		Vector2Data worldPos = mouseController->getRecalculateWorldPosition(world, scene->getCamera());

		Vector2Data tileId = world->tileCoorOnWorldPosition(worldPos);
		if (tileId.x < 0 || tileId.y < 0 || tileId.x > world->getWidth() - 1 || tileId.y > world->getHeight() - 1)
		{
			return;
		}
		int tileID = (tileId.y * world->getWidth() + tileId.x);
		
		if (mouseController->getMouseState() == MouseState::CLICK)
		{
			int built = scene->getBuilder()->Build(tileID);

			// akkor nem épített, nem is próbált építeni, tehát prolly selection
			if (built == 1)
			{
				// először tűz click check
				if (!world->PutOutFire(tileID))
				{
					#define DEBUG
#ifdef DEBUG
					Tile* t = world->getWrapper()->GetPointerToId(tileID);
#endif // DEBUG
					// ha nem tűz click akkor zóna
					selectedZone = world->getZoneStatsForTile(tileID);
				}
			}
		}
		else if (mouseController->getMouseState() == MouseState::DRAG)
		{
			scene->getBuilder()->HighlightArea(mouseController->getRecalculateWorldPosition(scene->getWorld(), scene->getCamera()), scene->getWorld());
			scene->getBuilder()->Highlight(tileID);
		}
		else
		{
			scene->getBuilder()->Highlight(tileID);
			scene->getBuilder()->UnHighlightArea();
		}
	}
	// update végi resetek és update-ek
	mouseController->ClearControlFrame();
#endif
}

/// <summary>
/// Renderelés
/// Először a világot jeleníti meg, majd az Overlay-eket
/// Overlay-be tartozik a kurzor, kijelölések, tűzesetek és helikopterek
/// </summary>
void CMyApp::Render()
{
#ifndef TESTING
	// töröljük a frampuffert (GL_COLOR_BUFFER_BIT) és a mélységi Z puffert (GL_DEPTH_BUFFER_BIT)
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cullcheck és vertex data konstruálás
	World* world = scene->getWorld();
	Camera* camera = scene->getCamera();

	Vertex* vert;
	std::vector<SubMap>* subs = world->getSubmaps();

	std::vector<Vector3Data> rects;
	rects.reserve(15'000);

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
		currRect.x -= 32;
		currRect.y -= 21;
		//rect y-jából tudok z-depth-et számolni, betolom egy -0.9 - 0.9 space-be
		//rect.z-ben alapból texid van
		float rectDepth = currRect.y / 64 / worldHeight;	//[0,1]
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
		GL_STREAM_DRAW);

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


	// day - night cycle
	float time = Time::instance->getFullTime();
	time /= 6;

	time = sin(time * M_PI + M_PI);
	time = time * 2 + 1;
	time /= 2;
	if (time < 0)
	{
		time = 0;
	}
	else if (time > 1)
	{
		time = 1;
	}

	// ha ez 1 akkor nappal van
	// ha 0 akkor éjjel
	// [0,1] között is lehet
	//time = 1;
	glUniform1f(timeCycleLoc, time);

	// kirajzolás
	//A draw hívásokhoz a VAO és a program bindolva kell legyenek (glUseProgram() és glBindVertexArray())
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawArrays(GL_QUADS, 0, vertCount);

	// VAO kikapcsolása
	glBindVertexArray(0);

	// --------------
	// OVERLAY RENDER
	// --------------

	Tile* cursor = Overlay::getCursor();
	int cursorSize = Overlay::getCursorSize();
	if (cursor == nullptr)
	{
		glUseProgram(0);
		return;
	}

	int selectedTiles = selectedZone.tileCount;
	
	std::vector<Fire>* fires = scene->getWorld()->getFires();
	int fireCount = fires->size();

	std::vector<Helicopter*>* helicopters = world->getHelicopters();
	int helicopterCount = helicopters->size();

	vertCount = 4 * cursorSize + 4 * selectedTiles + 4 * fireCount + 4 * helicopterCount;
	vert = new Vertex[vertCount];

	//cursor
	for (int i = 0; i < cursorSize; i++)
	{
		// rect indexei
		Vector3Data vec3data = { (cursor + i)->rect.i, (cursor + i)->rect.j, -0.97 };
		// index -> real position
		vec3data.x = (vec3data.x * 64) + (vec3data.y * 32);
		vec3data.y = (vec3data.y * (64 - 41));

		// position offset, hogy rect origin jó helyen legyen
		vec3data.x -= 32;
		vec3data.y -= 21;

		vert[i * 4] = { glm::vec3(vec3data.x, vec3data.y, vec3data.z), glm::vec3(0, 1, cursor->texId) };
		vert[i * 4 + 1] = { glm::vec3((vec3data.x + 64), vec3data.y, vec3data.z), glm::vec3(1, 1, cursor->texId) };
		vert[i * 4 + 2] = { glm::vec3((vec3data.x + 64), (vec3data.y + 64), vec3data.z), glm::vec3(1, 0, cursor->texId) };
		vert[i * 4 + 3] = { glm::vec3(vec3data.x, (vec3data.y + 64), vec3data.z), glm::vec3(0, 0, cursor->texId) };
	}
	
	// zóna highlight
	for (int i = cursorSize; i < cursorSize + selectedTiles; i++)
	{
		Tile t = selectedZone.tiles[i - cursorSize];
		t.texId = 41 + selectedZone.z->getType();
		// rect indexei
		Vector3Data vec3data = { t.rect.i, t.rect.j, -0.96 };
		// index -> real position
		vec3data.x = (vec3data.x * 64) + (vec3data.y * 32);
		vec3data.y = (vec3data.y * (64 - 41));

		// position offset, hogy rect origin jó helyen legyen
		vec3data.x -= 32;
		vec3data.y -= 21;

		vert[i * 4] = { glm::vec3(vec3data.x, vec3data.y, vec3data.z), glm::vec3(0, 1, t.texId) };
		vert[i * 4 + 1] = { glm::vec3((vec3data.x + 64), vec3data.y, vec3data.z), glm::vec3(1, 1, t.texId) };
		vert[i * 4 + 2] = { glm::vec3((vec3data.x + 64), (vec3data.y + 64), vec3data.z), glm::vec3(1, 0, t.texId) };
		vert[i * 4 + 3] = { glm::vec3(vec3data.x, (vec3data.y + 64), vec3data.z), glm::vec3(0, 0, t.texId) };
	}

	// tűz
	for (int i = cursorSize + selectedTiles; i < cursorSize + selectedTiles + fireCount; i++)
	{
		Tile* originalTile = fires->at(i - cursorSize - selectedTiles).getTargetTile();
		Tile t;
		t.rect = originalTile->rect;
		t.texId = 3;

		Vector3Data vec3data = { t.rect.i, t.rect.j, -0.94 };
		// index -> real position
		vec3data.x = (vec3data.x * 64) + (vec3data.y * 32);
		vec3data.y = (vec3data.y * (64 - 41));

		// position offset, hogy rect origin jó helyen legyen
		vec3data.x -= 32;
		vec3data.y -= 21;

		vert[i * 4] = { glm::vec3(vec3data.x, vec3data.y, vec3data.z), glm::vec3(0, 1, t.texId) };
		vert[i * 4 + 1] = { glm::vec3((vec3data.x + 64), vec3data.y, vec3data.z), glm::vec3(1, 1, t.texId) };
		vert[i * 4 + 2] = { glm::vec3((vec3data.x + 64), (vec3data.y + 64), vec3data.z), glm::vec3(1, 0, t.texId) };
		vert[i * 4 + 3] = { glm::vec3(vec3data.x, (vec3data.y + 64), vec3data.z), glm::vec3(0, 0, t.texId) };
	}

	// helicopter
	for (int i = cursorSize + selectedTiles + fireCount; i < cursorSize + selectedTiles + fireCount + helicopterCount; i++)
	{
		Tile heliTile = helicopters->at(i - cursorSize - selectedTiles - fireCount)->getTile();
		Tile t;
		t.rect = heliTile.rect;
		t.texId = 50 + heliTile.texId;


		Vector3Data vec3data = { t.rect.i, t.rect.j, -0.945 };

		// position offset, hogy rect origin jó helyen legyen
		vec3data.x -= 32;
		vec3data.y -= 21;

		vert[i * 4] = { glm::vec3(vec3data.x, vec3data.y, vec3data.z), glm::vec3(0, 1, t.texId) };
		vert[i * 4 + 1] = { glm::vec3((vec3data.x + 64), vec3data.y, vec3data.z), glm::vec3(1, 1, t.texId) };
		vert[i * 4 + 2] = { glm::vec3((vec3data.x + 64), (vec3data.y + 64), vec3data.z), glm::vec3(1, 0, t.texId) };
		vert[i * 4 + 3] = { glm::vec3(vec3data.x, (vec3data.y + 64), vec3data.z), glm::vec3(0, 0, t.texId) };
	}
	glBindBuffer(GL_ARRAY_BUFFER, overlay_vboID); // tegyük "aktívvá" a létrehozott VBO-t
	// töltsük fel adatokkal az aktív VBO-t
	glBufferData(GL_ARRAY_BUFFER,					// az aktív VBO-ba töltsünk adatokat
		sizeof(Vertex)* vertCount,		// ennyi bájt nagyságban
		vert,								// erről a rendszermemóriabeli címről olvasva
		//GL_STATIC_DRAW);					// úgy, hogy a VBO-nkba nem tervezünk ezután írni és minden kirajzoláskor felhasnzáljuk a benne lévő adatokat	
		GL_STREAM_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] vert;

	glBindVertexArray(overlay_vaoID);

	//overlay ne sötétedjen
	glUniform1f(timeCycleLoc, 2);
	glDrawArrays(GL_QUADS, 0, vertCount);

	// VAO kikapcsolása
	glBindVertexArray(0);

	// shader kikapcsolása
	glUseProgram( 0 );
#endif
}

#ifndef TESTING
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól a billentyűzet LENYOMÁS inputokat.
/// </summary>
/// <param name="key">Billentyűkód</param>
void CMyApp::KeyboardDown(SDL_KeyboardEvent& key)
{
	//std::cout << key.keysym.sym << std::endl;
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
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól a billentyűzet FELENGEDÉS inputokat.
/// </summary>
/// <param name="key">Billentyűkód</param>
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
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól az egér MOZGATÁS inputokat.
/// </summary>
/// <param name="mouse">Egér kód</param>
void CMyApp::MouseMove(SDL_MouseMotionEvent& mouse)
{
	mouseController->UpdateControlFrame({ (float)mouse.x, (float)mouse.y }, MouseState::MOVED);
}
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól az egér GOMBLENYOMÁS inputokat.
/// </summary>
/// <param name="mouse">Egér kód</param>
void CMyApp::MouseDown(SDL_MouseButtonEvent& mouse)
{
	mouseController->UpdateControlFrame({ (float)mouse.x, (float)mouse.y }, MouseState::DRAG);
	mouseController->setDragStart(scene->getWorld(), scene->getCamera());
}
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól az egér GOMBFELENGEDÉS inputokat.
/// </summary>
/// <param name="mouse">Egér kód</param>
void CMyApp::MouseUp(SDL_MouseButtonEvent& mouse)
{
	if (mouse.button == SDL_BUTTON_LEFT)
	{
		mouseController->UpdateControlFrame({ (float)mouse.x, (float)mouse.y }, MouseState::CLICK);
	}
	else if(mouse.button == SDL_BUTTON_RIGHT)
	{
		scene->getBuilder()->ChangeState(BuilderState::NOBUILD, BuilderSubState::NONE);
		mouseController->UpdateControlFrame({ (float)mouse.x, (float)mouse.y }, MouseState::CLICK);

		// clear zone selection
		selectedZone.tileCount = 0;
	}
	
}
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól az egér GÖRGŐ inputokat.
/// </summary>
/// <param name="mouse">Egér kód</param>
void CMyApp::MouseWheel(SDL_MouseWheelEvent& wheel)
{
}
/// <summary>
/// Ezzel a függvénnyel kapja meg az applikáció az ablaktól az új ablak méretét.
/// </summary>
/// <param name="_w">Új szélesség</param>
/// <param name="_h">Új magasság</param>
void CMyApp::Resize(int _w, int _h)
{
	glViewport(0, 0, _w, _h );
	//ez fontos
	scene->getWorld()->reCalculateOrigoOffset();
}
/// <summary>
/// Textúra betöltő függvény
/// </summary>
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


	//light mask

	GLuint texture2;
	SDL_Surface* surface2;
	surface2 = IMG_Load("light-mask.png");
	glGenTextures(1, &texture2);
	glActiveTexture(GL_TEXTURE0+1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface2->w, surface2->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface2->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glUniform1i(lightMaskLoc, 1);

	SDL_FreeSurface(surface);
}
#endif
/// <summary>
/// Külső elérésű függvény ami irányítja a játékos építkezésé módját.
/// </summary>
/// <param name="state">Elsődleges építkezési mód</param>
/// <param name="subState">Másodlagos építkezési mód</param>
void CMyApp::ChangeBuilderState(BuilderState state, BuilderSubState subState)
{
	scene->getBuilder()->ChangeState(state, subState);
}
/// <summary>
/// Külső elérésű függvény ami irányítja a játék sebességét.
/// </summary>
/// <param name="i"></param>
void CMyApp::ChangeSpeed(int i)
{
	scene->getGameTime()->changeSpeed(i);
}
/// <summary>
/// Játékidő getter
/// </summary>
/// <returns></returns>
std::string CMyApp::getGameTime()
{
	return scene->getGameTime()->getTimeString();
}
/// <summary>
/// GameState getter
/// </summary>
/// <returns></returns>
GameState* CMyApp::getState()
{
	return scene->getGameState();
}
/// <summary>
/// Kívülről ezzel lehet elérni, hogy a játékos melyik zónára kattintott rá.
/// </summary>
/// <returns></returns>
ZoneStatData* CMyApp::getSelectedZone()
{
	return &selectedZone;
}
/// <summary>
/// GameScene getter 
/// </summary>
/// <returns></returns>
GameScene* CMyApp::getScene()
{
	return scene;
}


