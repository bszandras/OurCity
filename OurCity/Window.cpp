#ifndef TESTING
#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <cstring>

#include "Window.h"

// imgui include-ok
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl_gl3.h>

#include "ZoneTools.h"

Window* Window::instance = nullptr;

int Window::SDLInit()
{
	//SDL cucc

	//
	// 1. l�p�s: inicializ�ljuk az SDL-t
	//

	// a grafikus alrendszert kapcsoljuk csak be, ha gond van, akkor jelezz�k �s l�pj�nk ki
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		// irjuk ki a hibat es termin�ljon a program
		std::cout << "[SDL initialization] Error during the SDL initialization: " << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 2. l�p�s: �ll�tsuk be az OpenGL-es ig�nyeinket, hozzuk l�tre az ablakunkat, ind�tsuk el az OpenGL-t
	//

	// 2a: OpenGL ind�t�s�nak konfigur�l�sa, ezt az ablak l�trehoz�sa el�tt kell megtenni!

	// be�ll�thatjuk azt, hogy pontosan milyen OpenGL context-et szeretn�nk l�trehozni - ha nem tessz�k, akkor
	// automatikusan a legmagasabb el�rhet� verzi�j�t kapjuk
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#ifdef _DEBUG 
	// ha debug m�d� a ford�t�s, legyen az OpenGL context is debug m�dban, ekkor m�k�dik a debug callback 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif 

	// �ll�tsuk be, hogy h�ny biten szeretn�nk t�rolni a piros, z�ld, k�k �s �tl�tszatlans�gi inform�ci�kat pixelenk�nt
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// duplapufferel�s
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// m�lys�gi puffer h�ny bites legyen
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// antialiasing - ha kell
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	// hozzuk l�tre az ablakunkat
	win = 0;
	win = SDL_CreateWindow("Our City",		// az ablak fejl�ce
		100,						// az ablak bal-fels� sark�nak kezdeti X koordin�t�ja
		100,						// az ablak bal-fels� sark�nak kezdeti Y koordin�t�ja
		width,						// ablak sz�less�ge
		height,						// �s magass�ga
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP);			// megjelen�t�si tulajdons�gok
	
	// ha nem siker�lt l�trehozni az ablakot, akkor �rjuk ki a hib�t, amit kaptunk �s l�pj�nk ki
	if (win == 0)
	{
		std::cout << "[Ablak l�trehoz�sa]Hiba az SDL inicializ�l�sa k�zben: " << SDL_GetError() << std::endl;
		return 1;
	}

	//
	// 3. l�p�s: hozzunk l�tre az OpenGL context-et - ezen kereszt�l fogunk rajzolni
	//

	context = SDL_GL_CreateContext(win);
	if (context == 0)
	{
		std::cout << "[OGL context creation] Error during the creation of the OGL context: " << SDL_GetError() << std::endl;
		return 1;
	}

	// megjelen�t�s: v�rjuk be a vsync-et
	// 0 - nincs vsync
	// 1 - van vsync
	SDL_GL_SetSwapInterval(swapIntervall);

	// ind�tsuk el a GLEW-t
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cout << "[GLEW] Error during the initialization of glew." << std::endl;
		return 1;
	}

	// k�rdezz�k le az OpenGL verzi�t
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

	// enged�lyezz�k �s �ll�tsuk be a debug callback f�ggv�nyt ha debug context-ben vagyunk 
	GLint context_flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &context_flags);
	if (context_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
		glDebugMessageCallback(GLDebugMessageCallback, nullptr);
	}

	//ez a f�ggv�ny NAGYON NEM v�gleges
	StartGameLoop();
}

int Window::StartGameLoop()
{
	// v�get kell-e �rjen a program fut�sa?
	bool quit = false;
	bool gameStarted = false;

	// alkalmaz�s p�ld�nya
	app = new CMyApp();
	
	if (!app->Init())
	{
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(win);
		std::cout << "[app.Init] Error during the initialization of the application!" << std::endl;
		return 1;
	}

	//SDL_Surface* image = SDL_LoadBMP("city.bmp");
	//SDL_Surface* surface = SDL_GetWindowSurface(win);

	//SDL_BlitSurface(image, NULL, surface, NULL);
	//SDL_UpdateWindowSurface(win);

	// imgui init
	ImGui_ImplSdlGL3_Init(win);

	ImGuiIO& io = ImGui::GetIO();
	ImFont* font1 = io.Fonts->AddFontFromFileTTF("New Super Mario Font U.ttf", 24.0f);
	ImFont* font3 = io.Fonts->AddFontFromFileTTF("New Super Mario Font U.ttf", 36.0f);
	ImFont* font2 = io.Fonts->AddFontFromFileTTF("Fluo Gums.ttf", 140.0f);

	while (!gameStarted && !quit) 
	{

		while (SDL_PollEvent(&event))
		{
			HandleEvents(quit, event);
		}

		ImGui_ImplSdlGL3_NewFrame(win);

		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGui::SetNextWindowPos(ImVec2((width * 0.5) - 250, (height * 0.5) - 200));
		ImGui::SetNextWindowSize(ImVec2(850, 600));

		ImGui::Begin("Text", &quit, window_flags);

			ImGui::PushFont(font2);

			ImGui::Text("OUR CITY");

			ImGui::PopFont();

		ImGui::End();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(200, 5, 30, 0));

		ImGui::SetNextWindowPos(ImVec2((width*0.5)-50,(height*0.5)));

		ImGui::Begin("Main Menu", &quit, window_flags);

			ImGui::PushFont(font3);

			ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));

			if (ImGui::Button("Start",ImVec2(115,45))) {
				gameStarted = true;
			}

			if (ImGui::Button("Quit", ImVec2(115, 45))) {
				quit = true;
			}

			ImGui::PopStyleColor();

			ImGui::PopFont();

		ImGui::End();

		ImGui::PopStyleColor();

		ImGui::Render();

		// sdl double buffering
		SDL_GL_SwapWindow(win);

	}

	//SDL_FreeSurface(image);
	//SDL_FreeSurface(surface);

	// start loop
	while (!quit)
	{

		while (SDL_PollEvent(&event))
		{
			// imgui input handling ezen bel�l
			HandleEvents(quit, event);
		}
		// imgui �gy kezd frame-et (nem window frame, hanem frame mint fps)
		ImGui_ImplSdlGL3_NewFrame(win);

		app->Update();
		app->Render();

		// imgui be�p�tett demo window
		//ImGui::ShowTestWindow();
		// imgui render, ez el� kell minden imguis cuccnak ker�lnie
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_AlwaysAutoResize;

		ImGuiWindowFlags wf = 0;
		wf |= ImGuiWindowFlags_NoResize;
		wf |= ImGuiWindowFlags_NoTitleBar;
		wf |= ImGuiWindowFlags_NoMove;

		ImGuiWindowFlags wfStat = 0;
		wfStat |= ImGuiWindowFlags_NoResize;
		wfStat |= ImGuiWindowFlags_NoMove;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(200, 5, 30, 0));
		ImGui::SetNextWindowPos(ImVec2(0.5f, 0.5f));

		ImGui::Begin("Options", &quit, window_flags);

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));

		if (ImGui::Button("ESC")) {
			app->ChangeSpeed(0);
			ImGui::OpenPopup("Menu");
		}
		if (ImGui::BeginPopupModal("Menu",NULL,wf)) {
			if (ImGui::Button("Resume")) {
				app->ChangeSpeed(1);
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Quit")) {
				quit = true;
			}

			ImGui::EndPopup();
		}

		if (ImGui::Button("Money")) {
			ImGui::OpenPopup("Money Statistics");
		}
		//float n = 1.0f;
		if (ImGui::BeginPopupModal("Money Statistics",NULL,wfStat)) 
		{
			if (ImGui::Button("Close")) 
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::Text((std::to_string(app->getState()->getMoney()) + " mobium").c_str());
			float* g = app->getScene()->getWorld()->getGlobalTaxRateHandle();
			ImGui::Text("Global Tax:");
			ImGui::SliderFloat("##G", g , 0.5f, 1.5f, "%.1f");

			float* h = app->getScene()->getWorld()->getHousingTaxRateHandle();
			ImGui::Text("Resident Zone Tax:");
			ImGui::SliderFloat("##R", h, 0.5f, 1.5f, "%.1f");

			float* s = app->getScene()->getWorld()->getServiceTaxRateHandle();
			ImGui::Text("Service Zone Tax:");
			ImGui::SliderFloat("##S", s, 0.5f, 1.5f, "%.1f");

			float* i = app->getScene()->getWorld()->getIndustrialTaxRateHandle();
			ImGui::Text("Industrial Zone Tax:");
			ImGui::SliderFloat("##I", i, 0.5f, 1.5f, "%.1f");

			ImGui::EndPopup();
		}

		if (ImGui::Button("Happiness")) {
			ImGui::OpenPopup("Happiness Statistics");
		}

		if (ImGui::BeginPopupModal("Happiness Statistics", NULL, wfStat))
		{
			if (ImGui::Button("Close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::Text("There will be statistics here!");

			ImGui::EndPopup();
		}
		/*
		if (ImGui::Button("Zone Stat Test")) {
			activeInfo = true;
			ImGui::SetNextWindowPos(ImVec2(width/2 - 50,height/2 - 50));
		}
		if (activeInfo) {
			ImGui::Begin("Zone Stat");
			
			if (ImGui::Button("Close")) {
				activeInfo = false;
			}

			ImGui::End();

		}
		*/
		

		ImGui::PopStyleColor();

		ImGui::End();

		Zone* z = app->getSelectedZone()->z;
		if (z != nullptr)
		{
			ImGuiWindowFlags zFlags = 0;
			//zFlags |= ImGuiWindowFlags_NoResize;
			//zFlags |= ImGuiWindowFlags_NoMove;
			//zFlags |= ImGuiWindowFlags_ChildWindow;

			//ImGui::SetNextWindowPos(ImVec2(width / 2 - 50, height / 2 - 50));
			ImGui::SetNextWindowPos(ImVec2(width -350, height / 2 - 50));
			//ImGui::Begin("Zone Stat", NULL, zFlags);
			ImGui::Begin("Zone Stat");

			std::string data = "";
			if (z->getType() == 0)
			{
				data = "Housing zone";
			}
			else if (z->getType() == 1)
			{
				data = "Industrial zone";
			}
			else
			{
				data = "Service zone";
			}
			ImGui::Text(data.c_str());
			data = "Residents: ";
			data += std::to_string(ZoneTools::getResidentCount(app->getSelectedZone(), app->getScene()->getWorld()));
			ImGui::Text(data.c_str());

			data = "Average happiness: ";
			data += std::to_string(ZoneTools::getAverageHappiness(app->getSelectedZone(), app->getScene()->getWorld(), app->getScene()->getResidentManager()));
			ImGui::Text(data.c_str());
			//ImGui::Text("Residents: " + )
			ImGui::Text("Tax:");
			ImGui::SliderFloat("", z->getTaxRateHandle(), 0.5f, 1.5f, "%.1f");
			/*
			if (ImGui::Button("Close")) {
				//activeInfo = false;
			}
			*/

			ImGui::End();
		}

		ImGui::SetNextWindowPos(ImVec2(width-215, 0.5f));

		ImGui::Begin("Time", &quit, window_flags);

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));

		if (ImGui::Button("Pause")) {
			app->ChangeSpeed(0);
		}
		ImGui::SameLine();
		if (ImGui::Button(">")) {
			app->ChangeSpeed(1);
		}
		ImGui::SameLine();
		if (ImGui::Button(">>")) {
			app->ChangeSpeed(2);
		}
		ImGui::SameLine();
		if (ImGui::Button(">>>")) {
			app->ChangeSpeed(3);
		}
		ImGui::Text("Time: ");
		ImGui::Text(app->getGameTime().c_str());

		ImGui::PopStyleColor();

		ImGui::End();

		//ImGui::SetCursorPos

		// EZ �GY NEM J�
		// hardcode-olt �rt�kek
		ImGui::SetNextWindowPos(ImVec2(width/2 - 140, height-80));

		ImGui::Begin("Zones", &quit, window_flags);

		ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(53, 121, 65, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, IM_COL32(200, 30, 65, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(200, 30, 65, 255));
		

		if (ImGui::Button("Resident")) {
			float wnposX = ImGui::GetWindowPos().x;
			float wnposY = ImGui::GetWindowPos().y;
			ImGui::SetNextWindowPos(ImVec2(wnposX + 5, wnposY - 35));

			// change builder state
			app->ChangeBuilderState(BuilderState::NOBUILD, BuilderSubState::NONE);
			ImGui::OpenPopup("ResidentP");
		}
		if (ImGui::BeginPopup("ResidentP")) {
			if (ImGui::Button("Build")) {
				ImGui::CloseCurrentPopup();

				// change builder state
				app->ChangeBuilderState(BuilderState::ZONE, BuilderSubState::HOUSINGZONE);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete")) {
				ImGui::CloseCurrentPopup();
				// change builder state
				app->ChangeBuilderState(BuilderState::ZONECANCEL, BuilderSubState::NONE);
			}
			//ImGui::GetMousePosOnOpeningCurrentPopup
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Industry")) {
			float wnposX = ImGui::GetWindowPos().x;
			float wnposY = ImGui::GetWindowPos().y;
			ImGui::SetNextWindowPos(ImVec2(wnposX + 5, wnposY - 35));

			// change builder state
			app->ChangeBuilderState(BuilderState::NOBUILD, BuilderSubState::NONE);
			ImGui::OpenPopup("IndustryP");
		}
		if (ImGui::BeginPopup("IndustryP")) {
			if (ImGui::Button("Build")) {
				ImGui::CloseCurrentPopup();

				// change builder state
				app->ChangeBuilderState(BuilderState::ZONE, BuilderSubState::INDUSTRIALZONE);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete")) {

				ImGui::CloseCurrentPopup();
				// change builder state
				app->ChangeBuilderState(BuilderState::ZONECANCEL, BuilderSubState::NONE);
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Service")) {
			float wnposX = ImGui::GetWindowPos().x;
			float wnposY = ImGui::GetWindowPos().y;
			ImGui::SetNextWindowPos(ImVec2(wnposX + 5, wnposY - 35));

			// change builder state
			app->ChangeBuilderState(BuilderState::NOBUILD, BuilderSubState::NONE);
			ImGui::OpenPopup("ServiceP");
		}
		if (ImGui::BeginPopup("ServiceP")) {
			if (ImGui::Button("Build")) {
				ImGui::CloseCurrentPopup();

				// change builder state
				app->ChangeBuilderState(BuilderState::ZONE, BuilderSubState::SERVICEZONE);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete")) {
				ImGui::CloseCurrentPopup();
				// change builder state
				app->ChangeBuilderState(BuilderState::ZONECANCEL, BuilderSubState::NONE);
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("Special")) {
			float wnposX = ImGui::GetWindowPos().x;
			float wnposY = ImGui::GetWindowPos().y;
			ImGui::SetNextWindowPos(ImVec2(wnposX + 5, wnposY - 35));

			// change builder state
			app->ChangeBuilderState(BuilderState::NOBUILD, BuilderSubState::NONE);
			ImGui::OpenPopup("SpecialP");
		}
		bool openMyPopUp = false;
		if (ImGui::BeginPopup("SpecialP")) {
			if (ImGui::Button("Build")) {
				openMyPopUp = true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete")) {
				// change builder state
				app->ChangeBuilderState(BuilderState::BUILDINGDESTROY, BuilderSubState::NONE);
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
		if (openMyPopUp) {
			ImGui::OpenPopup("SpecialBuilding");
		}
		if (ImGui::BeginPopupModal("SpecialBuilding",NULL,wf)) {
				if (ImGui::Button("Road")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::ROAD);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Police")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::POLICESTATION);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Stadium")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::STADIUM);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Fire Department")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::FIRESTATION);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Highschool")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::HIGHSCHOOL);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("University")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::UNIVERSITY);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Forest")) {
					// change builder state
					app->ChangeBuilderState(BuilderState::BUILDING, BuilderSubState::FOREST);
					ImGui::CloseCurrentPopup();
				}
				if (ImGui::Button("Close")) {
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

	// ha kil�pt�nk
	// takar�tson el maga ut�n az objektumunk
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
	// imgui megkapja az sdl-t�l az inputot
	// ez alapj�n d�nti el, hogy gombra nyomtunk-e vagy ablakot mozgattunk stb
	ImGui_ImplSdlGL3_ProcessEvent(&ev);

	// ezzel a k�t boollal tudjuk megcsin�lni, hogy ha gombot nyomunk
	// akkor alatta a z�n�t ne jel�lj�k ki
	bool is_mouse_captured = ImGui::GetIO().WantCaptureMouse; // kell-e az imgui-nak az eg�r
	bool is_keyboard_captured = ImGui::GetIO().WantCaptureKeyboard;	// kell-e az imgui-nak a billenty�zet
	//std::cout << is_mouse_captured << std::endl;
	switch (ev.type)
	{
	case SDL_QUIT:
		quit = true;
		break;
	case SDL_KEYDOWN:
		if (ev.key.keysym.sym == SDLK_ESCAPE)
			//quit = true;
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
		// N�h�ny platformon (pl. Windows) a SIZE_CHANGED nem h�v�dik meg az els� megjelen�skor.
		// Szerint�nk ez bug az SDL k�nyt�rban.
		// Ez�rt ezt az esetet k�l�n lekezelj�k, 
		// mivel a MyApp esetlegesen tartalmazhat ablak m�ret f�gg� be�ll�t�sokat, pl. a kamera aspect ratioj�t a perspective() h�v�sn�l.
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
		std::cout << "M�r van egy ablak l�trehozva." << std::endl;
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
#endif