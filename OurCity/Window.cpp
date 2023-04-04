#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <cstring>

#include "Window.h"

// imgui include-ok
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl_gl3.h>



Window* Window::instance = nullptr;

int Window::SDLInit()
{
	//SDL cucc

	//
	// 1. lépés: inicializáljuk az SDL-t
	//

	// a grafikus alrendszert kapcsoljuk csak be, ha gond van, akkor jelezzük és lépjünk ki
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		// irjuk ki a hibat es termináljon a program
		std::cout << "[SDL initialization] Error during the SDL initialization: " << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 2. lépés: állítsuk be az OpenGL-es igényeinket, hozzuk létre az ablakunkat, indítsuk el az OpenGL-t
	//

	// 2a: OpenGL indításának konfigurálása, ezt az ablak létrehozása elõtt kell megtenni!

	// beállíthatjuk azt, hogy pontosan milyen OpenGL context-et szeretnénk létrehozni - ha nem tesszük, akkor
	// automatikusan a legmagasabb elérhetõ verziójút kapjuk
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifdef _DEBUG 
	// ha debug módú a fordítás, legyen az OpenGL context is debug módban, ekkor mûködik a debug callback 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif 

	// állítsuk be, hogy hány biten szeretnénk tárolni a piros, zöld, kék és átlátszatlansági információkat pixelenként
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// duplapufferelés
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// mélységi puffer hány bites legyen
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// antialiasing - ha kell
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	// hozzuk létre az ablakunkat
	win = 0;
	win = SDL_CreateWindow("Our City",		// az ablak fejléce
		100,						// az ablak bal-felsõ sarkának kezdeti X koordinátája
		100,						// az ablak bal-felsõ sarkának kezdeti Y koordinátája
		width,						// ablak szélessége
		height,						// és magassága
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);			// megjelenítési tulajdonságok
	
	// ha nem sikerült létrehozni az ablakot, akkor írjuk ki a hibát, amit kaptunk és lépjünk ki
	if (win == 0)
	{
		std::cout << "[Ablak létrehozása]Hiba az SDL inicializálása közben: " << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 3. lépés: hozzunk létre az OpenGL context-et - ezen keresztül fogunk rajzolni
	//

	context = SDL_GL_CreateContext(win);
	if (context == 0)
	{
		std::cout << "[OGL context creation] Error during the creation of the OGL context: " << SDL_GetError() << std::endl;
		return 1;
	}

	// megjelenítés: várjuk be a vsync-et
	// 0 - nincs vsync
	// 1 - van vsync
	SDL_GL_SetSwapInterval(swapIntervall);

	// indítsuk el a GLEW-t
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "[GLEW] Error during the initialization of glew." << std::endl;
		return 1;
	}

	// kérdezzük le az OpenGL verziót
	int glVersion[2] = { -1, -1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	std::cout << "Running OpenGL " << glVersion[0] << "." << glVersion[1] << std::endl;

	if (glVersion[0] == -1 && glVersion[1] == -1)
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);

		std::cout << "[OGL context creation] Error during the inialization of the OGL context! Maybe one of the SDL_GL_SetAttribute(...) calls is erroneous." << std::endl;
		return 1;
	}

	// engedélyezzük és állítsuk be a debug callback függvényt ha debug context-ben vagyunk 
	GLint context_flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
	if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageCallback(GLDebugMessageCallback, nullptr);
	}

	//ez a függvény NAGYON NEM végleges
	StartGameLoop();
}

int Window::StartGameLoop()
{
	// véget kell-e érjen a program futása?
	bool quit = false;

	// alkalmazás példánya
	app = new CMyApp();
	
	if (!app->Init())
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);
		std::cout << "[app.Init] Error during the initialization of the application!" << std::endl;
		return 1;
	}
	// imgui init
	ImGui_ImplSdlGL3_Init(win);

	// start loop
	while (!quit)
	{

		while (SDL_PollEvent(&event))
		{
			// imgui input handling ezen belül
			HandleEvents(quit, event);
		}
		// imgui így kezd frame-et (nem window frame, hanem frame mint fps)
		ImGui_ImplSdlGL3_NewFrame(win);

		app->Update();
		app->Render();

		// imgui beépített demo window
		//ImGui::ShowTestWindow();
		// imgui render, ez elé kell minden imguis cuccnak kerülnie
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGuiWindowFlags wf = 0;
		wf |= ImGuiWindowFlags_NoResize;
		wf |= ImGuiWindowFlags_NoTitleBar;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(200, 5, 30, 0));
		ImGui::SetNextWindowPos(ImVec2(0.5f, 0.5f));

		ImGui::Begin("Options", &quit, window_flags);

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));

		if (ImGui::Button("ESC")) {
			ImGui::OpenPopup("Menu");
		}
		if (ImGui::BeginPopupModal("Menu")) {
			if (ImGui::Button("Resume")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::Button("Settings");
			ImGui::Button("Load");
			ImGui::Button("Save");
			if (ImGui::Button("Quit")) {
				quit = true;
			}

			ImGui::EndPopup();
		}

		if (ImGui::Button("Money")) {
			ImGui::OpenPopup("Money Statistics");
		}

		if (ImGui::BeginPopupModal("Money Statistics")) 
		{
			if (ImGui::Button("Resume")) 
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::Text("There will be statistics here!");

			ImGui::EndPopup();
		}

		if (ImGui::Button("Happiness")) {
			ImGui::OpenPopup("Happiness Statistics");
		}

		if (ImGui::BeginPopupModal("Happiness Statistics"))
		{
			if (ImGui::Button("Resume"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::Text("There will be statistics here!");

			ImGui::EndPopup();
		}

		ImGui::PopStyleColor();

		ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(width -230, 0.5f));

		ImGui::Begin("Time", &quit, window_flags);

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));

		if (ImGui::Button("Pause")) {
			app->ChangeSpeed(0);
		}
		ImGui::SameLine();
		if (ImGui::Button("Speed1")) {
			app->ChangeSpeed(2);
		}
		ImGui::SameLine();
		if (ImGui::Button("Speed2")) {
			app->ChangeSpeed(2);
		}
		ImGui::SameLine();
		if (ImGui::Button("Speed3")) {
			app->ChangeSpeed(2);
		}
		ImGui::Text("Time");

		ImGui::PopStyleColor();

		ImGui::End();

		//ImGui::SetCursorPos

		// EZ ÍGY NEM JÓ
		// hardcode-olt értékek
		ImGui::SetNextWindowPos(ImVec2(width/2 - 140, height-80));

		ImGui::Begin("Zones", &quit, window_flags);

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(200, 30, 65, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(200, 30, 65, 255));
		

		if (ImGui::Button("Resident")) {
			ImVec2 window_popup = ImGui::GetWindowPos();
			ImGui::OpenPopup("ResidentP");
		}
		if (ImGui::BeginPopup("ResidentP")) {
			if (ImGui::Button("Build")) {
				ImGui::CloseCurrentPopup();

				// change builder state
				app->ChangeBuilderState(BuilderState::ZONE, BuilderSubState::HOUSINGZONE);
			}
			if (ImGui::Button("Delete")) {
				ImGui::CloseCurrentPopup();
			}
			//ImGui::GetMousePosOnOpeningCurrentPopup
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Industry")) {
			ImGui::OpenPopup("IndustryP");
		}
		if (ImGui::BeginPopup("IndustryP")) {
			if (ImGui::Button("Build")) {
				ImGui::CloseCurrentPopup();

				// change builder state
				app->ChangeBuilderState(BuilderState::ZONE, BuilderSubState::INDUSTRIALZONE);
			}
			if (ImGui::Button("Delete")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Service")) {
			ImGui::OpenPopup("ServiceP");
		}
		if (ImGui::BeginPopup("ServiceP")) {
			if (ImGui::Button("Build")) {
				ImGui::CloseCurrentPopup();

				// change builder state
				app->ChangeBuilderState(BuilderState::ZONE, BuilderSubState::SERVICEZONE);
			}
			if (ImGui::Button("Delete")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Special")) {
			ImGui::OpenPopup("SpecialP");
		}
		if (ImGui::BeginPopup("SpecialP")) {
			if (ImGui::Button("Build")) {
				ImGui::OpenPopup("SpecialBuilding");
			}
			if (ImGui::BeginPopupModal("SpecialBuilding")) {
				if (ImGui::Button("Road")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::ROAD);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Police")) {
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Stadium")) {
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Fire Department")) {
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Highschool")) {
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("University")) {
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Forest")) {
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Close")) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			if (ImGui::Button("Delete")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		//app->scene->time->changespeed

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		//ImGui::SetCursorPosX(ImGui::GetWindowSize().x / 2);

		ImGui::End();

		ImGui::PopStyleColor();

		ImGui::Render();

		// sdl double buffering
		SDL_GL_SwapWindow(win);
	}

	// ha kiléptünk
	// takarítson el maga után az objektumunk
	app->Clean();
	
	//imgui cleanup
	ImGui_ImplSdlGL3_Shutdown();
	//sdl cleanup
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);

	return 0;
}

int Window::HandleEvents(bool& quit, SDL_Event ev)
{
	// imgui megkapja az sdl-tõl az inputot
	// ez alapján dönti el, hogy gombra nyomtunk-e vagy ablakot mozgattunk stb
	ImGui_ImplSdlGL3_ProcessEvent(&ev);

	// ezzel a két boollal tudjuk megcsinálni, hogy ha gombot nyomunk
	// akkor alatta a zónát ne jelöljük ki
	bool is_mouse_captured = ImGui::GetIO().WantCaptureMouse; // kell-e az imgui-nak az egér
	bool is_keyboard_captured = ImGui::GetIO().WantCaptureKeyboard;	// kell-e az imgui-nak a billentyûzet
	//std::cout << is_mouse_captured << std::endl;
	switch (ev.type)
	{
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_KEYDOWN:
		if (ev.key.keysym.sym == SDLK_ESCAPE)
			quit = true;
		app->KeyboardDown(ev.key);
		break;
	case SDL_KEYUP:
		app->KeyboardUp(ev.key);
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (!is_mouse_captured)
		{
			app->MouseDown(ev.button);
		}
		
		break;
	case SDL_MOUSEBUTTONUP:
		if (!is_mouse_captured)
		{
			app->MouseUp(ev.button);
		}
		
		break;
	case SDL_MOUSEWHEEL:
		app->MouseWheel(ev.wheel);
		break;
	case SDL_MOUSEMOTION:
		app->MouseMove(ev.motion);
		break;
	case SDL_WINDOWEVENT:
		// Néhány platformon (pl. Windows) a SIZE_CHANGED nem hívódik meg az elsõ megjelenéskor.
		// Szerintünk ez bug az SDL könytárban.
		// Ezért ezt az esetet külön lekezeljük, 
		// mivel a MyApp esetlegesen tartalmazhat ablak méret függõ beállításokat, pl. a kamera aspect ratioját a perspective() hívásnál.
		if (ev.window.event == SDL_WINDOWEVENT_SHOWN)
		{
			int w, h;
			SDL_GetWindowSize(win, &w, &h);

			width = w;
			height = h;

			app->Resize(w, h);
		}
		if (ev.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			width = ev.window.data1;
			height = ev.window.data2;
			std::cout << width << " " << height << std::endl;
			app->Resize(ev.window.data1, ev.window.data2);
		}
		break;
	}
	return 0;
}

Window::Window(int w, int h, int swap)
{
	if (instance != nullptr)
	{
		std::cout << "Már van egy ablak létrehozva." << std::endl;
		return;
	}
	else
	{
		instance = this;
	}

	width = w;
	height = h;
	swapIntervall = swap;

	SDLInit();
}

Window::~Window()
{
	delete app;
}

int Window::getWidth()
{
	return width;
}

int Window::getHeight()
{
	return height;
}
