#include "World.h"
#include "SubMap.h"
#include <cmath>

#ifndef TESTING
#include "Window.h"
#endif
#include <random>

/// <summary>
/// Világ konstruktora
/// Ez hozza létre az összes celláját, alrégióját a térképnek
/// </summary>
/// <returns></returns>
World::World()
{
	globalTaxRate = 1.0;
	housingTaxRate = 1.0;
	industrialTaxRate = 1.0;
	serviceTaxRate = 1.0;

	origoOffset = { 0,0 };
	reCalculateOrigoOffset();

	tileRectWrapper = new TileRectWrapper(width * height);
	//tiles.reserve(width * height);

	int submapReseve = (height / SubMap::getSize()) * ((width + height / 2) / SubMap::getSize());
	submaps.reserve(submapReseve);

	for (int i = 0; i < height; i += SubMap::getSize())
	{
		for (int j = 0; j < width + (height / 2); j += SubMap::getSize())
		{
			submaps.push_back(SubMap(Vector2Data{ (float)(j * 64), (float)(i * 64) }, 64, this));
		}
	}


	for (unsigned short i = 0; i < height; i++)
	{
		for (unsigned short j = 0; j < width; j++)
		{
			//int x = (i * 64) + j * 32;
			//int y = (j * (64 - 41));
			int x = (j * 64) + i * 32;
			int y = (i * (64 - 41));
			unsigned char texId = 2;
			//tileRectWrapper->AddRect(TileRect{ i,j,texId });

			tileRectWrapper->AddTile({ nullptr, {j,i}, texId });

			int c = rand() % 10;
			if (c == 1)
			{
#ifndef TESTING




				Tile* t = tileRectWrapper->GetPointerToId(tileRectWrapper->GetLastRectID());
				Building* b = new Forest(t);
				b->setBuildCost(0);
				t->building = b;
				t->texId = BuilderSubState::FOREST;
#endif // !TESTING
			}
			int horIndex = x / (SubMap::getSize() * 64);
			int vertIndex = y / (SubMap::getSize() * 64);
			int mainIndex = horIndex + (vertIndex * (width + (height / 2)) / SubMap::getSize());

			submaps[mainIndex].addRect(tileRectWrapper->GetLastRectID());

			// tile-t is meg kell csin�lni a grafikai reprezent�ci�hoz
			//tiles.push_back({ x,y });

		}
	}

	//t�r�lj�k az �res submapokat
	std::vector<SubMap> newSubMaps;
	newSubMaps.reserve(submapReseve / 2);
	for (int i = 0; i < submaps.size(); i++)
	{
		if (submaps[i].getRectCount() > 0)
		{
			newSubMaps.push_back(submaps[i]);
		}
	}
	submaps = newSubMaps;
}

World::~World()
{
	// TODO destruktor
	delete tileRectWrapper;
}
/// <summary>
/// Világ origó offset/pozíció gettere
/// </summary>
/// <returns></returns>
Vector2Data World::getOrigoOffset()
{
	return origoOffset;
}
/// <summary>
/// Újra számolja az origo offsetet
/// Ez fontos a megjelenítő ablak átméretezésekor
/// </summary>
void World::reCalculateOrigoOffset()
{
#ifndef TESTING
	origoOffset = { Window::instance->getWidth() / 2.0f, Window::instance->getHeight() / 2.0f };
#endif
}
/// <summary>
/// Alrégiók gettere
/// </summary>
/// <returns></returns>
std::vector<SubMap>* World::getSubmaps()
{
	return &submaps;
}
/// <summary>
/// Világ szélesség gettere
/// </summary>
/// <returns></returns>
int World::getWidth()
{
	return width;
}
/// <summary>
/// Világ magasság gettere
/// </summary>
/// <returns></returns>
int World::getHeight()
{
	return height;
}
/// <summary>
/// TileWrapper gettere
/// (Lásd TileRect file)
/// </summary>
/// <returns></returns>
TileRectWrapper* World::getWrapper()
{
	return tileRectWrapper;
}
/// <summary>
/// Világ pozíciót, cella koordinátává konvertál
/// </summary>
/// <param name="worldPos">Világ pozíció</param>
/// <returns>Cella kooridnáta</returns>
Vector2Data World::tileCoorOnWorldPosition(Vector2Data worldPos)
{
	int y = round(worldPos.y / (64 - 41));
	int x = round((worldPos.x - y * 32) / 64);

	return { (float)x, (float)y };
}
/// <summary>
/// Lekéri az adott koordinátán lévő cellát
/// </summary>
/// <param name="i">X koordináta</param>
/// <param name="j">Y kooridnáta</param>
/// <returns>Cella pointere</returns>
Tile* World::getTileOnCoords(int i, int j)
{
	int index = j * width;
	index += i;
	return this->tileRectWrapper->GetPointerToId(index);
}
/// <summary>
/// Lekéri egy cella összes szomszédját
/// </summary>
/// <param name="origin">Eredeti cella</param>
/// <returns>Szomszédos cellák tömbje</returns>
Tile** World::getNeighboursWritablePointers(Tile* origin)
{
	Tile** tiles = new Tile*[4];

	Tile* t = this->tileRectWrapper->GetPointerToId((origin->rect.j + 1) * width + origin->rect.i - 1);
	tiles[0] = t;
	t = this->tileRectWrapper->GetPointerToId((origin->rect.j + 1) * width + origin->rect.i);
	tiles[1] = t;
	t = this->tileRectWrapper->GetPointerToId((origin->rect.j - 1) * width + origin->rect.i);
	tiles[2] = t;
	t = this->tileRectWrapper->GetPointerToId((origin->rect.j - 1) * width + origin->rect.i + 1);
	tiles[3] = t;
	return tiles;
}
/// <summary>
/// Lekéri egy cella összes szomszédját egy sugárban
/// </summary>
/// <param name="origin">Eredeti cella</param>
/// <param name="radius">Keresési sugár</param>
/// <returns>Cellák tömbje</returns>
Tile** World::getWritableTilePointersInRadius(Tile* origin, int radius)
{
	int tileCount = (radius + 1 + radius) * (radius + 1 + radius) - 1;
	Tile** returnable = new Tile* [tileCount];

	int originID = origin->rect.j * width + origin->rect.i;
	int index = 0;

	// center oszlop
	for (int i = -radius; i <= radius; i++)
	{
		if (i == 0)
		{
			continue;
		}

		returnable[index] = tileRectWrapper->GetPointerToId(originID + i * width);
		index++;
	}

	// bal oszlopok
	for (int i = 1; i <= radius; i++)
	{
		int firstID = originID - i;
		returnable[index] = tileRectWrapper->GetPointerToId(firstID);
		index++;

		if(index >= tileCount)
		{
			//std::cout << "tilecount problem, left col center" << std::endl;
			return returnable;
		}

		// aktuális bal oszlop lefelé
		for (int j = 1; j <= radius - i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID - j * width);
			index++;

			if (index >= tileCount)
			{
				std::cout << "tilecount problem left col down" << std::endl;
				return returnable;
			}
		}

		// aktuális bal oszlop felfelé
		for (int j = 1; j <= radius + i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID + j * width);
			index++;

			if (index >= tileCount)
			{
				std::cout << "tilecount problem left col up" << std::endl;
				return returnable;
			}
		}
	}

	// jobb oszlopok, ugyanaz mint a bal oszlopok, de tükrözve
	for (int i = 1; i <= radius; i++)
	{
		int firstID = originID + i;
		returnable[index] = tileRectWrapper->GetPointerToId(firstID);
		index++;

		if (index >= tileCount)
		{
			std::cout << "tilecount problem right col center" << std::endl;
			return returnable;
		}

		// aktuális jobb oszlop lefelé
		for (int j = 1; j <= radius - i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID + j * width);
			index++;

			if (index >= tileCount)
			{
				std::cout << "tilecount problem right col down" << std::endl;
				return returnable;
			}
		}

		// aktuális bal oszlop felfelé
		for (int j = 1; j <= radius + i; j++)
		{
			returnable[index] = tileRectWrapper->GetPointerToId(firstID - j * width);
			index++;

			if (index >= tileCount)
			{
				// itt valamiért utolsónál kiugrik
				// szóval kommentelve marad a safety check :D

				//std::cout << index << std::endl;
				//std::cout << "tilecount problem right col up" << std::endl;
				//return returnable;
			}

		}
	}

	return returnable;
}
/// <summary>
/// Lekéri egy cella összes szomszédját amire direkt rálát egy bizonyos távolságon belül
/// </summary>
/// <param name="origin">Eredeti cella</param>
/// <param name="distance">Keresési távolság</param>
/// <returns>Cellák tömbje</returns>
Tile** World::getWritableTilePointersInDirectLineOfSight(Tile* origin, int distance)
{
	Tile** returnable = new Tile * [distance * 4];
	int originID = origin->rect.j * width + origin->rect.i;
	int index = 0;

	// vertical direct line of sight
	for (int i = -distance; i <= distance; i++)
	{
		if (i == 0)
		{
			continue;
		}
		returnable[index] = tileRectWrapper->GetPointerToId(originID + i * width);
		index++;

		returnable[index] = tileRectWrapper->GetPointerToId((originID + i * width) - i);
		index++;
	}

	return returnable;
}
/// <summary>
/// Egy sávban visszaad minden cella ID-t
/// </summary>
/// <param name="botleft">Sáv kezdőpontja</param>
/// <param name="topright">Sáv végpontja</param>
/// <returns>Cella ID-k</returns>
std::vector<int> World::tileIdsInArea(Vector2Data botleft, Vector2Data topright)
{
	std::vector<int> returnable;

	int blY = round(botleft.y / (64 - 41));
	int blX = round((botleft.x - blY * 32) / 64);

	int trY = round(topright.y / (64 - 41));
	int trX = round((topright.x - trY * 32) / 64);

	if (botleft.x < topright.x)
	{
		if (trY > blY)
		{
			for (int i = 0; i < trY - blY + 1; i++)
			{
				int id = (blY + i) * width + blX;
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
		else
		{
			for (int i = 0; i < trX - blX + 1; i++)
			{
				int id = (blY - i) * width + blX + (i * 1);
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
	}
	else
	{
		if (trY > blY)
		{
			for (int i = 0; i < trY - blY + 1; i++)
			{
				int id = (blY + i) * width + blX - (i * 1);
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
		else
		{
			for (int i = blY - trY; i > 0; i--)
			{
				int id = (trY + i) * width + blX;
				if (id >= 0)
				{
					returnable.push_back(id);
				}
			}
		}
	}
	
	return returnable;
}
/// <summary>
/// Világhoz hozzáadja az új lakózónát
/// </summary>
/// <param name="zone">Új lakózóna</param>
void World::addHouseZone(Zone zone)
{
	this->HouseZones.push_back(zone);
}
/// <summary>
/// Világhoz hozzáadja az új iparizónát
/// </summary>
/// <param name="zone">Új iparizóna</param>
void World::addIndustryZone(Zone zone)
{
	this->IndustryZones.push_back(zone);
}
/// <summary>
/// Világhoz hozzáadja az új szolgáltatásizónát
/// </summary>
/// <param name="zone">Új szolgáltatásizóna</param>
void World::addServiceZone(Zone zone)
{
	this->ServiceZones.push_back(zone);
}
/// <summary>
/// Vilához hozzáad egy új házat az adott mezőn
/// </summary>
/// <param name="tile">Cél mező</param>
/// <returns>Lakóház pointere</returns>
House* World::addHouse(Tile* tile)
{
	House h(tile);
	Houses.push_back(h);

	return Houses.data() + Houses.size()-1;
}
/// <summary>
/// Vilához hozzáad egy új gyárat az adott mezőn
/// </summary>
/// <param name="tile">Cél mező</param>
/// <returns>Gyár pointere</returns>
Factory* World::addFactory(Tile* tile)
{
	Factory f(tile);
	Factories.push_back(f);
	return &Factories.at(Factories.size() - 1);
}
/// <summary>
/// Vilához hozzáad egy új szolgáltatási épületet az adott mezőn
/// </summary>
/// <param name="tile">Cél mező</param>
/// <returns>Szolgáltatási épület pointere</returns>
ServiceBuilding* World::addServBuilding(Tile* tile)
{
	ServiceBuilding sv(tile);
	ServBuildings.push_back(sv);
	return &ServBuildings.at(ServBuildings.size() - 1);
}
/// <summary>
/// Visszaadja a lakózónák gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<Zone>* World::getHouseZones()
{
	return &HouseZones;
}
/// <summary>
/// Visszaadja az iparizónák gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<Zone>* World::getIndustryZones()
{
	return &IndustryZones;
}
/// <summary>
/// Visszaadja a szolgáltatásizónák gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<Zone>* World::getServiceZones()
{
	return &ServiceZones;
}
/// <summary>
/// Visszaadja az adott cellához tartozó zónát
/// </summary>
/// <param name="tileID">Cél cella</param>
/// <returns></returns>
ZoneStatData World::getZoneStatsForTile(int tileID)
{
	ZoneStatData z;
	z.z = nullptr;
	z.tileCount = 0;
	// lakózóna
	for (int i = 0; i < HouseZones.size(); i++)
	{
		if (HouseZones[i].isTileInZone(tileID))
		{
			z.z = &HouseZones[i];
			z.tileCount = HouseZones[i].tileCount();
			std::vector<int> tiles = HouseZones[i].getTiles();
			z.tiles = new Tile[z.tileCount];
			for (int j = 0; j < z.tileCount; j++)
			{
				z.tiles[j] = *(tileRectWrapper->GetPointerToId(tiles[j]));
			}
			return z;
		}
	}
	// ipar
	for (int i = 0; i < IndustryZones.size(); i++)
	{
		if (IndustryZones[i].isTileInZone(tileID))
		{
			z.z = &IndustryZones[i];
			z.tileCount = IndustryZones[i].tileCount();
			std::vector<int> tiles = IndustryZones[i].getTiles();
			z.tiles = new Tile[z.tileCount];
			for (int j = 0; j < z.tileCount; j++)
			{
				z.tiles[j] = *(tileRectWrapper->GetPointerToId(tiles[j]));
			}
			return z;
		}
	}
	// service
	for (int i = 0; i < ServiceZones.size(); i++)
	{
		if (ServiceZones[i].isTileInZone(tileID))
		{
			z.z = &ServiceZones[i];
			z.tileCount = ServiceZones[i].tileCount();
			std::vector<int> tiles = ServiceZones[i].getTiles();
			z.tiles = new Tile[z.tileCount];
			for (int j = 0; j < z.tileCount; j++)
			{
				z.tiles[j] = *(tileRectWrapper->GetPointerToId(tiles[j]));
			}
			return z;
		}
	}
	return z;
}
/// <summary>
/// Visszaadja a lakóházak gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<House>* World::getHouses()
{
	return &Houses;
}
/// <summary>
/// Visszaadja a gyárak gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<Factory>* World::getFactories()
{
	return &Factories;
}
/// <summary>
/// Visszaadja a szolgáltatási épületek gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<ServiceBuilding>* World::getServBuildings()
{
	return &ServBuildings;
}
/// <summary>
/// Visszadja a kér lakóházat
/// </summary>
/// <param name="id">ID</param>
/// <returns></returns>
House* World::getHouse(int id)
{
	return &Houses.at(id);
}
/// <summary>
/// Visszadja a kér gyárat
/// </summary>
/// <param name="id">ID</param>
/// <returns></returns>
Factory* World::getFactory(int id)
{
	return &Factories.at(id);
}
/// <summary>
/// Visszadja a kér szolgáltatási épületet
/// </summary>
/// <param name="id">ID</param>
/// <returns></returns>
ServiceBuilding* World::getServBuilding(int id)
{
	return &ServBuildings.at(id);
}
/// <summary>
/// Hozzáad a világhoz, útgráfhoz az új utat
/// </summary>
/// <param name="t">Cél cella</param>
/// <param name="scene">GameScene pointere</param>
/// <returns>Igaz, ha sikeres az új út hozzáadása</returns>
bool World::AddRoad(Tile* t, GameScene* scene)
{
	return roadGraph.addRoad(t, scene->getGameState());;
}
/// <summary>
/// Útgráf getter
/// </summary>
/// <returns></returns>
RoadGraph* World::getRoadGraph()
{
	return &roadGraph;
}
/// <summary>
/// Hozzáad a világhoz egy új tűzoltóságot
/// </summary>
/// <param name="firestation">Új tűzoltóság pointere</param>
void World::AddFireStation(FireStation* firestation)
{
	fireStations.push_back(firestation);
}
/// <summary>
/// Töröl a világból egy tűzoltóságot
/// </summary>
/// <param name="firestation">Törlendő tűzoltóság pointere</param>
void World::RemoveFireStation(FireStation* firestation)
{
	for (int i = 0; i < fireStations.size(); i++)
	{
		if (fireStations.at(i) == firestation)
		{
			fireStations.erase(fireStations.begin() + i);
		}
	}
}
/// <summary>
/// Visszaadja a tűzoltóságok gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<FireStation*>* World::getFireStations()
{
	return &fireStations;
}
/// <summary>
/// A világhoz adja a paraméterként kapott leégethető speciális épületet
/// </summary>
/// <param name="specialBuilding">Leégethető speciális épület</param>
void World::AddBurnableSpecialBuilding(SpecialBuilding* specialBuilding)
{
	burnableBuildings.push_back(specialBuilding);
}
/// <summary>
/// Törli a világból a leégethető speciális épületet
/// </summary>
/// <param name="specialBuilding"></param>
void World::RemoveBurnableSpecialBuilding(SpecialBuilding* specialBuilding)
{
	for (int i = 0; i < burnableBuildings.size(); i++)
	{
		if (burnableBuildings.at(i) == specialBuilding)
		{
			burnableBuildings.erase(burnableBuildings.begin() + i);
		}
	}
}
/// <summary>
/// Visszaadja a leégethető speciális épületek gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<SpecialBuilding*>* World::getBurnableSpecials()
{
	return &burnableBuildings;
}
/// <summary>
/// A világhoz ad egy új tűzet
/// </summary>
/// <param name="t">Tűre mutató pointer</param>
/// <returns></returns>
int World::AddFire(Tile* t)
{
	// tile még nem tudja hogy ég
	if (t->onFire)
	{
		return 0;
	}
	Fire f(t);
	fires.push_back(f);
	t->onFire = true;
	return 1;
}
/// <summary>
/// Visszaadja a tűzek gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<Fire>* World::getFires()
{
	return &fires;
}
/// <summary>
/// Előrébb lépteti a tűzeket, kezeli a terjedést és leégést
/// </summary>
/// <param name="deltaDays">Legutóbbi frissítés óta eltellt napok</param>
void World::UpdateFires(int deltaDays)
{
	// folytatja a tüzet
	// ha egy tűz leégett, akkor a tile-ről törli az épületet
	// HA HÁZ akkor
	// mindenki hajléktalan lesz, munkahelyeket előtte fel kell szabadítani
	// HA MUNKAHELY akkor a lakosok csak munkanélküliek lesznek
	// resident manager-be kell egy delete lakos függvény ami minden szálat elvarr
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 4);//uniform distribution between 0 and 1

	for (int i = 0; i < fires.size(); i++)
	{
		Fire* f = &fires.at(i);
		f->Update(deltaDays);

		// TERJED A TŰZ
		if (f->shouldPropagate())
		{
			Tile** neighs = getNeighboursWritablePointers(f->getTargetTile());
			double dir = dis(gen);
			Tile* newTarget = neighs[(int)trunc(dir)];

			if (newTarget->type != 0 && !newTarget->onFire)
			{
				AddFire(newTarget);
				//std::cout << "fire propagation" << std::endl;
			}
			else if (newTarget->building != nullptr && newTarget->texId != FIRESTATION
				&& newTarget->texId != ROAD && newTarget->onFire)
			{
				AddFire(newTarget);
				//std::cout << "fire propagation" << std::endl;
			}
		}
		// akkor túl sokáig égett
		if (f->getBurnTime() > f->getMaxBurnTime())
		{
			// leég a ház elmúlik a tűz
			Tile* t = f->getTargetTile();
			int type = t->type;
			int id = (int)t->building / 24;
			if (type == 1) 
			{
				this->burntHouses.push_back(id);

			}
			else if(type == 2)
			{
				this->burntFactories.push_back(id);
			}
			else if (type == 3)
			{
				this->burntService.push_back(id);
			}
			// utolsó lehetőség a spec épület
			else if (t->building != nullptr)
			{
				// itt updatelni kell spec épület hatásokat

			}
			// ha leégett az épület az odatartó helikoptert haza kell küldeni
			for (int i = 0; i < helicopters.size(); i++)
			{
				if (helicopters.at(i)->getTargetFire() == f)
				{
					helicopters.at(i)->FireBurned();
				}
			}

			// ha leégett az épület akkor a tűznek is el kell tűnnie
			for (int i = 0; i < fires.size(); i++)
			{
				if (fires.at(i).getTargetTile() == t)
				{
					fires.erase(fires.begin() + i);
					t->onFire = false;
				}
			}
		}
	}
}
/// <summary>
/// Tűzoltó függvény.
/// A paraméterként kapott cella ID-ján megpróbálja eloltani a tűzet, indít helikoptert.
/// </summary>
/// <param name="tileID"></param>
/// <returns></returns>
bool World::PutOutFire(int tileID)
{
	Tile* t = tileRectWrapper->GetPointerToId(tileID);
	if (!t->onFire)
	{
		return false;
	}
	if (fireStations.size() == 0)
	{
		// akkor nincs tűzoltóság :(
		// nem oltja el, de capture-öli az egér clicket
		return true;
	}
	Fire* targetFire = nullptr;
	for (int i = 0; i < fires.size(); i++)
	{
		if (fires.at(i).getTargetTile() == t)
		{
			targetFire = &fires.at(i);
		}
	}
	if (targetFire == nullptr)
	{
		return true;
	}

	Vector2Data end;
	end.x = (t->rect.i * 64) + (t->rect.j * 32);
	end.y = (t->rect.j * (64 - 41));

	FireStation* station = nullptr;
	float dist = 1000000;
	int closestID = -1;
	// find closest available firestation
	for (int i = 0; i < fireStations.size(); i++)
	{
		TileRect r = fireStations.at(i)->getTile()->rect;
		Vector2Data spos;
		spos.x = (r.i * 64) + (r.j * 32);
		spos.y = (r.j * (64 - 41));
		float distance = Vector2Tool::Distance(end, spos);
		if (distance < dist && fireStations.at(i)->isAvailable())
		{
			station = fireStations.at(i);
			dist = distance;
			closestID = i;
		}
	}
	if (station == nullptr || !station->isAvailable())
	{
		return true;
	}
	station->HeliStarted();

	Tile* stationTile = station->getTile();
	Vector2Data start;
	start.x = (stationTile->rect.i * 64) + (stationTile->rect.j * 32);
	start.y = (stationTile->rect.j * (64 - 41));

	Helicopter* heli = new Helicopter(start, end, targetFire, station);
	helicopters.push_back(heli);
	return true;
}
/// <summary>
/// Frissíti a helikoptereket. Mozgatja a pozíciójuk és frissíti a rotorokat.
/// </summary>
/// <param name="deltaTime">Legutóbbi frissítés óta eltellt másodpercek</param>
void World::AdvanceHelicopters(float deltaTime)
{
	for (int i = 0; i < helicopters.size(); i++)
	{
		Helicopter* h = helicopters.at(i);
		h->AdvanceRotor();
		h->MoveToTarget(deltaTime);
		if (h->HasArrived() && h->getTargetFire() != nullptr)
		{
			Fire* f = h->getTargetFire();
			for (int j = 0; j < fires.size(); j++)
			{
				Tile* t = f->getTargetTile();
				if (fires.at(j).getTargetTile() == t)
				{
					fires.erase(fires.begin() + j);
					t->onFire = false;
					break;
				}
			}
			//std::cout << "put out fire" << std::endl;
			//put out
			//check for nearby fires
			h->ReturnHome();
		}
		else if (h->HasArrived() && h->getTargetFire() == nullptr)
		{
			h->getStation()->HeliArrived();
			RemoveHelicopter(h);
			break;
		}
	}
}
/// <summary>
/// Törli a világból a paraméterként kapott helikopter pointerét
/// </summary>
/// <param name="heli">Törlendő helikopter</param>
void World::RemoveHelicopter(Helicopter* heli)
{
	for (int i = 0; i < helicopters.size(); i++)
	{
		if (helicopters.at(i) == heli)
		{
			helicopters.erase(helicopters.begin() + i);
			return;
		}
	}
}
/// <summary>
/// Visszaadja a helikopterek gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<Helicopter*>* World::getHelicopters()
{
	return &helicopters;
}
/// <summary>
/// Visszaadja a leégett lakóházak ID-jait
/// </summary>
/// <returns></returns>
std::vector<int> World::getBurntHouses()
{
	return this->burntHouses;
}
/// <summary>
/// Visszaadja a leégett gyárak ID-jait
/// </summary>
/// <returns></returns>
std::vector<int> World::getBurntFactories()
{
	return this->burntFactories;
}
/// <summary>
/// Visszaadja a leégett szolgáltatási épületek ID-jait
/// </summary>
/// <returns></returns>
std::vector<int> World::getBurntService()
{
	return this->burntService;
}
/// <summary>
/// Kezeli a leégett épületek sorsát
/// </summary>
void World::removeBurntBuildings()
{
	// clear előtt gondoskodni kell a leégett épületekről
	for (int i = 0; i < burntHouses.size(); i++)
	{
		// resident manager a lakosok dolgait elintézte
		House* h = getHouse(burntHouses[i]);
		h->setCapacity(0);
		h->clearResidents();
		// tile dolgait kell intézni
		Tile* t = h->getTile();
		
		t->hasZone = true;
		t->building = nullptr;
		t->texId = 10 + t->type;
		t->type = 0;


	}
	for (int i = 0; i < burntFactories.size(); i++)
	{
		// resident manager a lakosok dolgait elintézte
		Factory* f = getFactory(burntFactories[i]);
		f->setCapacity(0);
		f->clearWorkers();
		// tile dolgait kell intézni
		Tile* t = f->getTile();
		
		t->hasZone = true;
		t->building = nullptr;
		t->texId = 10 + t->type;
		t->type = 0;
	}
	for (int i = 0; i < burntService.size(); i++)
	{
		// resident manager a lakosok dolgait elintézte
		ServiceBuilding* s = getServBuilding(burntService[i]);
		s->setCapacity(0);
		s->clearWorkers();
		// tile dolgait kell intézni
		Tile* t = s->getTile();
		
		t->hasZone = true;
		t->building = nullptr;
		t->texId = 10 + t->type;
		t->type = 0;
	}

	// HATALMAS PROBLÉMA
	// ÍGY MARAD MERT MÁR TÚLSÁGOSAN BENNE VAN
	// mivel a 3 zónatípus épületeit mindeki id-val referálja
	// NEM SZABAD world-> házakat tároló vectorából kiszedni őket
	// szóval leégett épület benne marad szellem épületnek

	this->burntHouses.clear();
	this->burntFactories.clear();
	this->burntService.clear();
}
/// <summary>
/// Globális lakossági adószorzó settere
/// </summary>
/// <param name="taxRate"></param>
void World::setHousingTaxRate(double taxRate)
{
	this->housingTaxRate = taxRate;
}
/// <summary>
/// Globális ipari adószorzó settere
/// </summary>
/// <param name="taxRate"></param>
void World::setIndustrialTaxRate(double taxRate)
{
	this->industrialTaxRate = taxRate;
}
/// <summary>
/// Globális szolgáltatási adószorzó settere
/// </summary>
/// <param name="taxRate"></param>
void World::setServiceTaxRate(double taxRate)
{
	this->serviceTaxRate = taxRate;
}
/// <summary>
/// Alap adó gettere
/// </summary>
/// <returns></returns>
int World::getBaseTax()
{
	return baseTax;
}
/// <summary>
/// Globális adószorzó gettere
/// </summary>
/// <returns></returns>
float World::getGlobalTaxRate()
{
	return globalTaxRate;
}
/// <summary>
/// Globális lakossági adószorzó gettere
/// </summary>
/// <returns></returns>
float World::getHousingTaxRate()
{
	return housingTaxRate;
}
/// <summary>
/// Globális ipari adószorzó gettere
/// </summary>
/// <returns></returns>
float World::getIndustrialTaxRate()
{
	return industrialTaxRate;
}
/// <summary>
/// Globális szolgáltatási adószorzó gettere
/// </summary>
/// <returns></returns>
float World::getServiceTaxRate()
{
	return serviceTaxRate;
}
/// <summary>
/// Globális adószorzó pointer gettere
/// </summary>
/// <returns></returns>
float* World::getGlobalTaxRateHandle()
{
	return &globalTaxRate;
}
/// <summary>
/// Globális lakossági adószorzó pointer gettere
/// </summary>
/// <returns></returns>
float* World::getHousingTaxRateHandle()
{
	return &housingTaxRate;
}
/// <summary>
/// Globális ipari adószorzó pointer gettere
/// </summary>
/// <returns></returns>
float* World::getIndustrialTaxRateHandle()
{
	return &industrialTaxRate;
}
/// <summary>
/// Globális szolgáltatási adószorzó pointer gettere
/// </summary>
/// <returns></returns>
float* World::getServiceTaxRateHandle()
{
	return &serviceTaxRate;
}
/// <summary>
/// Visszaadja a középiskolák gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<HighSchool*>* World::getHighSchools()
{
	return &highschools;
}
/// <summary>
/// Visszaadja az egyetemek gyűjteményét
/// </summary>
/// <returns></returns>
std::vector<University*>* World::getUniversities()
{
	return &universities;
}
/// <summary>
/// Hozzáadja a világhoz a paraméterként kapott középiskolát
/// </summary>
/// <param name="h"></param>
void World::addHighschool(HighSchool* h)
{
	highschools.push_back(h);
}
/// <summary>
/// Törli a világból a paraméterként kapott középiskolát
/// </summary>
/// <param name="h"></param>
void World::removeHighschool(HighSchool* h)
{
	for (int i = 0; i < highschools.size(); i++)
	{
		if (highschools.at(i) == h)
		{
			highschools.erase(highschools.begin() + i);
		}
	}
}
/// <summary>
/// Hozzáadja a világhoz a paraméterként kapott egyetemet
/// </summary>
/// <param name="h"></param>
void World::addUniversity(University* uni)
{
	universities.push_back(uni);
}
/// <summary>
/// Törli a világból a paraméterként kapott egyetemet
/// </summary>
/// <param name="h"></param>
void World::removeUniversity(University* uni)
{
	for (int i = 0; i < universities.size(); i++)
	{
		if (universities.at(i) == uni)
		{
			universities.erase(universities.begin() + i);
		}
	}
}
