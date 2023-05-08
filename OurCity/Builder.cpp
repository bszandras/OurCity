#include "Builder.h"
#include "BuildingsInclude.h"
#include "Overlay.h"

Builder::Builder(TileRectWrapper* wrapper, MouseController* mouse, World* world, GameScene* scene)
{
	Builder::wrapper = wrapper;
	Builder::mouse = mouse;
	Builder::world = world;
	Builder::scene = scene;
}

Builder::~Builder()
{
}
void Builder::ChangeState(BuilderState state, BuilderSubState subState)
{
	primaryState = state;
	secondaryState = subState;

	if (state == BuilderState::NOBUILD)
	{
		//wrapper->UpdateTexIdById(currentlyHighlighted, currentTex);
		Overlay::Cursor(false, { 0 , 0 });
		Overlay::MultiCursor(false, nullptr, 4);
	}
	else
	{

	}
}

int Builder::Build(int where)
{
	switch (primaryState)
	{
	case NOBUILD:
		return 1;
		break;
	case ZONE:
		SelectZone();
		break;
	case ZONECANCEL:
		RemoveTileFromZone(where);
		break;
	case BUILDING:
		BuildSpecBuilding(where);
		break;
	case BUILDINGDESTROY:
		DestroySpecBuilding(where);
		break;
	default:
		break;
	}
	return 0;
}
void Builder::BuildSpecBuilding(int where)
{
	Tile* tile = wrapper->GetPointerToId(where);
	if (tile->hasZone || tile->building != nullptr || tile->type != 0)
	{
		//van itt valami más
		return;
	}
	switch (secondaryState)
	{
	case ROAD:
		// a tile-hoz utat kötést a gráf oldja meg és a pénz checket is
		if (world->AddRoad(wrapper->GetPointerToId(where), scene))
		{
			wrapper->UpdateTexIdById(where, 14);
			if (currentlyHighlighted == where)
			{
				currentTex = 14;
			}
		}
		
		break;
	case FOREST:
	{
		Tile* tile = wrapper->GetPointerToId(where);
		{
			Forest* build = new Forest(tile);
			bool succ = BuildSpecBuilding(tile, build, where, FOREST);

			if (succ == false)
			{
				delete build;
			}
		}
		break;
	}
	case POLICESTATION:
	{
		Tile* tile = wrapper->GetPointerToId(where);
		if (world->getRoadGraph()->isAdjacent(tile))
		{
			PoliceStation* build = new PoliceStation(tile);
			bool succ = BuildSpecBuilding(tile, build, where, POLICESTATION);

			if (!succ)
			{
				delete build;
			}
		}
		break;
	}
	case FIRESTATION:
	{
		Tile* tile = wrapper->GetPointerToId(where);
		if (world->getRoadGraph()->isAdjacent(tile))
		{
			FireStation* build = new FireStation(tile);
			bool succ = BuildSpecBuilding(tile, build, where, FIRESTATION);
			
			if (!succ)
			{
				delete build;
			}
		}
		break;
	}
	case HIGHSCHOOL:
	{
		Tile* tile = wrapper->GetPointerToId(where);

		HighSchool* build = new HighSchool(tile);
		bool succ = BuildBigSpecBuilding(tile, build, where, HIGHSCHOOL);

		if (!succ)
		{
			delete build;
		}
		
		break;
	}
	case UNIVERSITY:
	{
		Tile* tile = wrapper->GetPointerToId(where);

		University* build = new University(tile);
		bool succ = BuildBigSpecBuilding(tile, build, where, UNIVERSITY);

		if (!succ)
		{
			delete build;
		}
		
		break;
	}
	case STADIUM:
	{
		Tile* tile = wrapper->GetPointerToId(where);

		Stadium* build = new Stadium(tile);
		bool succ = BuildBigSpecBuilding(tile, build, where, STADIUM);

		if (!succ)
		{
			delete build;
		}
		
		break;
	}
	default:
		break;
	}
}
bool Builder::BuildSpecBuilding(Tile* tile, Building* building, int where, int tex)
{
	if (tile->building != nullptr)
	{
		std::cout << "there is a building already here" << std::endl;
		return false;
	}

	if (!scene->getGameState()->hasEnough(building->getBuildCost()))
	{
		//Ekkor is lehet építeni! -> mínuszba megy a város és kölcsönbõl mûködik
		std::cout << "not enough money for <-building->" << std::endl;
		return false;
	}

	wrapper->GetPointerToId(where)->building = building;

	wrapper->UpdateTexIdById(where, tex);

	scene->getGameState()->addToMaintenance(building->getMaintenanceCost());

	if (tex == FIRESTATION)
	{
		FireStation* f = (FireStation*)building;
		world->AddFireStation(f);
		//update firestation
		int radius = f->getRange();
		Tile** tiles = world->getWritableTilePointersInRadius(tile, radius);
		
		int tileCount = (radius + 1 + radius) * (radius + 1 + radius) - 1;

		// ennyinek elégnek kéne lennie
		std::vector<Tile*> passable;
		passable.reserve(tileCount);

		for (int i = 0; i < tileCount; i++)
		{
			if (tiles[i] == tile)
			{
				continue;
			}
			passable.push_back(tiles[i]);
		}
		f->UpdateAreaAfterBuilding(passable.data(), passable.size());
	}
	else if (tex == POLICESTATION)
	{
		PoliceStation* f = (PoliceStation*)building;
		//update firestation
		int radius = f->getRange();
		Tile** tiles = world->getWritableTilePointersInRadius(tile, radius);

		int tileCount = (radius + 1 + radius) * (radius + 1 + radius) - 1;

		// ennyinek elégnek kéne lennie
		std::vector<Tile*> passable;
		passable.reserve(tileCount);

		for (int i = 0; i < tileCount; i++)
		{
			if (tiles[i] == tile)
			{
				continue;
			}
			passable.push_back(tiles[i]);
		}
		f->UpdateAreaAfterBuilding(passable.data(), passable.size());
	}
	else if (tex != FOREST && tex != ROAD)
	{
		world->AddBurnableSpecialBuilding((SpecialBuilding*)building);
	}
	/*
	if (currentlyHighlighted == where)
	{
		currentTex = tex;
	}
	*/

	// radius demo
	/*
	if (tex == FOREST)
	{
		int r = 1;
		Tile** tiles = world->getWritableTilePointersInRadius(tile, r);
		int tileCount = (r + 1 + r) * (r + 1 + r) - 1;

		for (int i = 0; i < tileCount; i++)
		{
			tiles[i]->texId = 11;
		}
	}
	// direct line of sight demo
	if (tex == FOREST)
	{
		int r = 2;
		int tileCount = r * 4;
		Tile** tiles = world->getWritableTilePointersInDirectLineOfSight(tile, r);

		for (int i = 0; i < tileCount; i++)
		{
			tiles[i]->texId = 12;
		}
	}
	*/
	return true;
}
bool Builder::BuildBigSpecBuilding(Tile* tile, Building* building, int where, int tex)
{
	Tile* base1 = tile;
	Tile* base2 = world->getWrapper()->GetPointerToId(where + world->getWidth());
	Tile* base3 = world->getWrapper()->GetPointerToId(where + world->getWidth() - 1);
	Tile* base4 = world->getWrapper()->GetPointerToId(where + world->getWidth() * 2 - 1);

	if (base1->building != nullptr || base2->building != nullptr || base1->type != 0 || base2->type != 0)
	{
		std::cout << "there is a building already here - highschool" << std::endl;
		return false;
	}
	if (tex == UNIVERSITY || tex == STADIUM)
	{
		if (base3->building != nullptr || base4->building != nullptr || base3->type != 0 || base4->type != 0)
		{
			std::cout << "there is a building already here" << std::endl;
			return false;
		}
	}

	RoadGraph* road = world->getRoadGraph();

	if (!road->isAdjacent(base1) && !road->isAdjacent(base2))
	{
		if (tex != HIGHSCHOOL)
		{
			if (!road->isAdjacent(base3) && !road->isAdjacent(base4))
			{
				std::cout << "big building not next to road" << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "big building not next to road - highschool" << std::endl;
			return false;
		}
	}
	
	if (!scene->getGameState()->hasEnough(building->getBuildCost()))
	{
		std::cout << "not enough money for <-building->" << std::endl;
		return false;
	}

	scene->getGameState()->addToMaintenance(building->getMaintenanceCost());

	base1->building = building;
	base2->building = building;

	if (secondaryState != HIGHSCHOOL)
	{
		base3->building = building;
		base4->building = building;
	}

	// LEGACY
	for (int i = 0; i < areaHighlightedIds.size(); i++)
	{
		wrapper->UpdateTexIdById(areaHighlightedIds[i], tex);
		areaHighlightedTexes[i] = tex;
	}
	//wrapper->UpdateTexIdById(where, tex);
	if (currentlyHighlighted == where)
	{
		currentTex = tex;
	}
	// LEGACY

	//update stadium
	if (tex == STADIUM)
	{
		// EZ FOS KÓD
		// DE MÛKÖDIK :)
		Stadium* s = (Stadium*)building;
		int range = s->getRange();

		Tile** tiles = world->getWritableTilePointersInRadius(base1, range);
		int tileCount = (range + 1 + range) * (range + 1 + range) - 1;

		// ennyinek elégnek kéne lennie
		std::vector<Tile*> passable;
		passable.reserve((range + 2 + range) * (range + 2 + range));

		for (int i = 0; i < tileCount; i++)
		{
			if (tiles[i] == base1 || tiles[i] == base2 || tiles[i] == base3 || tiles[i] == base4)
			{
				continue;
			}
			passable.push_back(tiles[i]);
		}

		// maradék 3 stadion cella környéke
		tiles = world->getWritableTilePointersInRadius(base2, range);
		for (int i = 0; i < tileCount; i++)
		{
			if (tiles[i] == base1 || tiles[i] == base2 || tiles[i] == base3 || tiles[i] == base4)
			{
				continue;
			}
			bool contains = false;
			for (int j = 0; j < passable.size(); j++)
			{
				
				if (passable[j] == tiles[i])
				{
					contains = true;
					break;
				}
			}
			if (!contains)
			{
				passable.push_back(tiles[i]);
			}
		}
		tiles = world->getWritableTilePointersInRadius(base3, range);
		for (int i = 0; i < tileCount; i++)
		{
			if (tiles[i] == base1 || tiles[i] == base2 || tiles[i] == base3 || tiles[i] == base4)
			{
				continue;
			}
			bool contains = false;
			for (int j = 0; j < passable.size(); j++)
			{
				if (passable[j] == tiles[i])
				{
					contains = true;
					break;
				}
			}
			if (!contains)
			{
				passable.push_back(tiles[i]);
			}
		}
		tiles = world->getWritableTilePointersInRadius(base4, range);
		for (int i = 0; i < tileCount; i++)
		{
			if (tiles[i] == base1 || tiles[i] == base2 || tiles[i] == base3 || tiles[i] == base4)
			{
				continue;
			}
			bool contains = false;
			for (int j = 0; j < passable.size(); j++)
			{
				if (passable[j] == tiles[i])
				{
					contains = true;
					break;
				}
			}
			if (!contains)
			{
				passable.push_back(tiles[i]);
			}
		}

		s->UpdateAreaAfterBuilding(passable.data(), passable.size());
	}
	else if (tex == HIGHSCHOOL)
	{
		HighSchool* h = (HighSchool*)building;
		world->addHighschool(h);
	}
	else if (tex == UNIVERSITY)
	{
		University* h = (University*)building;
		world->addUniversity(h);
	}


	return true;
}
bool Builder::DestroySpecBuilding(int where)
{
	Tile* tile = wrapper->GetPointerToId(where);
	if (tile->building == nullptr || tile->type != 0)	// ha nem 0 akkor ház ipar vagy service, azt sem szabad bontani
	{
		std::cout << "there is nothing here to destroy" << std::endl;
		return false;
	}

	if (world->getRoadGraph()->searchRoadByCoords(tile->rect.i, tile->rect.j))
	{
		if (world->getRoadGraph()->hasBuildingNext(tile, world->getNeighboursWritablePointers(tile)))
		{
			std::cout << "ut mellett epulet" << std::endl;
			return false;
		}
		scene->getGameState()->income(tile->building->getBuildCost() / 2);
		scene->getGameState()->subFromMaintenance(tile->building->getMaintenanceCost());
		world->getRoadGraph()->removeRoad(tile);
		tile->building = nullptr;

		wrapper->UpdateTexIdById(where, 2);
		if (currentlyHighlighted == where)
		{
			currentTex = 2;
		}
		return true;
	}
	else
	{
		Building* b = tile->building;
		if (b->getTileSize() > 1)
		{
			//building update ?
			if (tile->texId == STADIUM)
			{
				Stadium* s = (Stadium*)b;
				s->UpdateAreaAfterDestruction();
			}
			else if (tile->texId == HIGHSCHOOL)
			{
				HighSchool* h = (HighSchool*)b;
				world->removeHighschool(h);
			}
			else if (tile->texId == UNIVERSITY)
			{
				University* h = (University*)b;
				world->removeUniversity(h);
			}

			// 3x3-ban ellenõrizni és akkor tuti megtaláljuk a hozzá tartozó tile-okat
			Tile* top1 = world->getWrapper()->GetPointerToId(where + world->getWidth());
			Tile* top2 = world->getWrapper()->GetPointerToId(where + world->getWidth() - 1);
			Tile* highest = world->getWrapper()->GetPointerToId(where + world->getWidth() * 2 - 1);
			Tile* bot1 = world->getWrapper()->GetPointerToId(where - world->getWidth());
			Tile* bot2 = world->getWrapper()->GetPointerToId(where - world->getWidth() + 1);
			Tile* lowest = world->getWrapper()->GetPointerToId(where - world->getWidth() * 2 + 1);
			Tile* left = world->getWrapper()->GetPointerToId(where - 1);
			Tile* right = world->getWrapper()->GetPointerToId(where + 1);

			if (top1->building == b)
			{
				top1->building = nullptr;
				int id = where + world->getWidth();
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (top2->building == b)
			{
				top2->building = nullptr;
				int id = where + world->getWidth() - 1;
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (highest->building == b)
			{
				highest->building = nullptr;
				int id = where + world->getWidth() * 2 - 1;
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (bot1->building == b)
			{
				bot1->building = nullptr;
				int id = where - world->getWidth();
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (bot2->building == b)
			{
				bot2->building = nullptr;
				int id = where - world->getWidth() + 1;
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (lowest->building == b)
			{
				lowest->building = nullptr;
				int id = where - world->getWidth() * 2 + 1;
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (left->building == b)
			{
				left->building = nullptr;
				int id = where - 1;
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}
			if (right->building == b)
			{
				right->building = nullptr;
				int id = where + 1;
				wrapper->UpdateTexIdById(id, 2);
				if (currentlyHighlighted == id)
				{
					currentTex = 2;
				}
			}

			tile->building = nullptr;
			wrapper->UpdateTexIdById(where, 2);
			if (currentlyHighlighted == where)
			{
				currentTex = 2;
			}

			scene->getGameState()->income(b->getBuildCost() / 2);
			scene->getGameState()->subFromMaintenance(b->getMaintenanceCost());
			delete b;
			return true;
		}
		else
		{
			wrapper->GetPointerToId(where)->building = nullptr;

			// TODO
			// ide fognak kerülni a spec épület update-ek

			// tûzoltóságot remove-olni kell
			if (b->getTile()->texId == FIRESTATION)
			{
				FireStation* f = (FireStation*)b;
				world->RemoveFireStation(f);
				f->UpdateAreaAfterDestruction();
			}
			else if (b->getTile()->texId != FOREST && b->getTile()->texId != ROAD)
			{
				world->AddBurnableSpecialBuilding((SpecialBuilding*)b);
			}

			scene->getGameState()->income(b->getBuildCost() / 2);
			scene->getGameState()->subFromMaintenance(b->getMaintenanceCost());
			delete b;

			wrapper->UpdateTexIdById(where, 2);
			if (currentlyHighlighted == where)
			{
				currentTex = 2;
			}
			return true;
		}
	}
}
void Builder::SelectZone()
{
	// debug 0,0-ból indul a zone highlight
	switch (secondaryState)
	{
	case NONE:
		std::cout << "something went fucky wucky" << std::endl;
		return;
		break;
	case HOUSINGZONE:
	{
		Zone zone(0);
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			Tile* tile = wrapper->GetPointerToId(areaHighlightedIds[i]);
			if (tile -> hasZone || tile -> building != nullptr)
			{
				continue;
			}
			wrapper->GetPointerToId(areaHighlightedIds[i])->hasZone = true;
			wrapper->UpdateTexIdById(areaHighlightedIds[i], 11);

			// push tile into zone
			zone.addTile(areaHighlightedIds[i]);
		}
		world->addHouseZone(zone);
		break;
	}
	case INDUSTRIALZONE:
	{
		Zone zone(1);
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			Tile* tile = wrapper->GetPointerToId(areaHighlightedIds[i]);
			if (tile->hasZone || tile->building != nullptr)
			{
				continue;
			}
			wrapper->GetPointerToId(areaHighlightedIds[i])->hasZone = true;
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 12);

			// create zone and push tile into it
			zone.addTile(areaHighlightedIds[i]);
		}
		world->addIndustryZone(zone);
		break;
	}
	case SERVICEZONE:
	{
		Zone zone(2);
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			Tile* tile = wrapper->GetPointerToId(areaHighlightedIds[i]);
			if (tile->hasZone || tile->building != nullptr)
			{
				continue;
			}
			wrapper->GetPointerToId(areaHighlightedIds[i])->hasZone = true;
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 13);

			// create zone and push tile into it
			zone.addTile(areaHighlightedIds[i]);
		}
		world->addServiceZone(zone);
		break;
	}
	default:
		std::cout << "something went fucky wucky" << std::endl;
		return;
		break;
	}
	currentlyHighlighted = 0;
	currentTex = 0;
	areaHighlightedIds.clear();
	areaHighlightedTexes.clear();
}
void Builder::RemoveTileFromZone(int where)
{
	Tile* tile = wrapper->GetPointerToId(where);
	if (tile->building != nullptr || tile->type != 0)
	{
		return;
	}
	tile->type = 0;
	tile->hasZone = false;

	// egyelõre ez így szar de mûködik
	for (int j = 0; j < 3; j++)
	{
		std::vector<Zone>* zones;
		switch (j)
		{
		case 0:
			zones = world->getHouseZones();
			break;
		case 1:
			zones = world->getIndustryZones();
			break;
		case 2:
			zones = world->getServiceZones();
			break;
		default:
			std::cout << "valami óriási gebasz van a zóna törléssel" << std::endl;
			return;
			break;
		}

		for (int i = 0; i < zones->size(); i++)
		{
			std::vector<int> idsBefore = zones->at(i).getTiles();
			if (zones->at(i).removeTile(where))
			{
				// elég csak where-t update-elni
				// de sokkal biztosabb ha az egész zóna id-jait update-eljük
				wrapper->UpdateTexIdById(where, 2);
				/*
				std::vector<int> ids = zones->at(i).getTiles();

				// unhighlight
				for (int i = 0; i < idsBefore.size(); i++)
				{
					wrapper->UpdateTexIdById(idsBefore[i], 2);
				}
				// highlight whats left
				for (int i = 0; i < ids.size(); i++)
				{
					wrapper->UpdateTexIdById(ids[i], 11 + j);
				}

				if (currentlyHighlighted == where)
				{
					currentTex = 2;
				}
				*/
				return;
			}
		}
	}
}
void Builder::Highlight(int target)
{
	// if big building selected, reroute highlight
	if (secondaryState == HIGHSCHOOL || secondaryState == UNIVERSITY || secondaryState == STADIUM)
	{
		HighlightBigBuilding(target);
		return;
	}

	// unhighlight previous highlight
	// wrapper->UpdateTexIdById(currentlyHighlighted, currentTex);

	if (primaryState == NOBUILD)
	{
		return;
	}

	// store current highlight data
	// currentlyHighlighted = target;
	// currentTex = wrapper->GetRectsById(&target, 1)->texId;

	// new highlight
	// buildstate dependant highlighting is possible here
	// wrapper->UpdateTexIdById(target, 10);
	Tile* highlit = wrapper->GetPointerToId(target);
	Overlay::Cursor(true, { (float)highlit->rect.i, (float)highlit->rect.j });
}
void Builder::HighlightBigBuilding(int base)
{
	//unhighlight
	for (int i = 0; i < areaHighlightedIds.size(); i++)
	{
		wrapper->UpdateTexIdById(areaHighlightedIds[i], areaHighlightedTexes[i]);
	}

	areaHighlightedIds.clear();
	areaHighlightedTexes.clear();

	switch (secondaryState)
	{
	case HIGHSCHOOL:
	{
		//alap
		areaHighlightedIds.push_back(base);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&base, 1)->texId);
		//felette 1
		int second = base + world->getWidth();
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
		break;
	}
	case UNIVERSITY:
	{
		//alap
		areaHighlightedIds.push_back(base);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&base, 1)->texId);
		//felette 1
		int second = base + world->getWidth();
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
		//felette 2
		second = base + world->getWidth() - 1;
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
		//felette 3
		second = base  + world->getWidth() * 2 - 1;
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
		
		break;
	}
		break;
	case STADIUM:
	{
		//alap
		areaHighlightedIds.push_back(base);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&base, 1)->texId);
		//felette 1
		int second = base + world->getWidth();
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
		//felette 2
		second = base + world->getWidth() - 1;
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
		//felette 3
		second = base + world->getWidth() * 2 - 1;
		areaHighlightedIds.push_back(second);
		areaHighlightedTexes.push_back(wrapper->GetRectsById(&second, 1)->texId);
	}
		break;
	default:
		std::cout << "oriasi a gebasz ha idejutunk -> builder highlightbigbuilding" << std::endl;
		return;
		break;
	}

	int size = areaHighlightedIds.size();
	Vector2Data* positions = new Vector2Data[size];
	for (int i = 0; i < areaHighlightedIds.size(); i++)
	{
		//wrapper->UpdateTexIdById(areaHighlightedIds[i], 10);
		Tile* t = wrapper->GetPointerToId(areaHighlightedIds[i]);
		positions[i] = {(float)t->rect.i, (float)t->rect.j};
	}
	Overlay::MultiCursor(true, positions, size);
}
void Builder::HighlightArea(Vector2Data mouseWorldPosition, World* world)
{
#ifndef TESTING
	if (primaryState != BuilderState::ZONE)
	{
		return;
	}

	Vector2Data corner1 = mouse->getWorldDragStart();
	Vector2Data corner2 = mouseWorldPosition;

	//ide kell egy check, hogy ha túl kicsi a távolság a két sarok között akkor return-öljön

	UnHighlightArea();

	std::vector<int> ids;
	ids = world->tileIdsInArea(corner1, corner2);

	for (int i = 0; i < ids.size(); i++)
	{
		Tile* tile = wrapper->GetPointerToId(ids[i]);
		if (tile->hasZone || tile->building != nullptr)
		{
			continue;
		}

		if (std::find(areaHighlightedIds.begin(), areaHighlightedIds.end(), ids[i]) == areaHighlightedIds.end())
		{
			areaHighlightedIds.push_back(ids[i]);
			areaHighlightedTexes.push_back(world->getWrapper()->GetRectsById(&ids[i], 1)->texId);
		}
		int highlight = secondaryState;
		highlight += 10;
		world->getWrapper()->UpdateTexIdById(ids[i], highlight);
	}
#endif

}
void Builder::UnHighlightArea()
{
#ifndef TESTING
	if (areaHighlightedIds.size() == 0
		|| secondaryState == HIGHSCHOOL || secondaryState == UNIVERSITY || secondaryState == STADIUM)
	{
		return;
	}

	for (int i = 0; i < areaHighlightedIds.size(); i++)
	{
		world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], areaHighlightedTexes[i]);
	}

	areaHighlightedIds.clear();
	areaHighlightedTexes.clear();
#endif
}

House* Builder::BuildHouse(Tile* tile)
{
	if (!world->getRoadGraph()->isAdjacent(tile))
	{
		return nullptr;
	}

	House* h = world->addHouse(tile);
	tile->building = nullptr;
	tile->building += world->getHouses()->size()-1;
	tile->texId = 21 + 3;
	tile->type = 1;

	/*
	House* h = &(world->getHouses()->at((int)tile->building / 24));
	Factory* h = &(world->getFactories()->at((int)tile->building / 24));
	ServiceBuilding* h = &(world->getServBuildings()->at((int)tile->building / 24));
	*/
	//std::cout << world->getHouses()->size() - 1 << std::endl;
	//std::cout << tile->building << std::endl;
	//std::cout << (int)tile->building / 24 << std::endl;

	return h;
}

Factory* Builder::BuildFactory(Tile* tile)
{
	if (!world->getRoadGraph()->isAdjacent(tile))
	{
		return nullptr;
	}

	Factory* f = world->addFactory(tile);
	tile->building = nullptr;
	tile->building += world->getFactories()->size() - 1;
	tile->texId = 22 + 3;
	tile->type = 2;

	//std::cout << world->getFactories()->size() - 1 << std::endl;
	//std::cout << tile->building << std::endl;
	//std::cout << (int)tile->building / 24 << std::endl;


	//
	// NEGATÍV UPDATE
	//

	int radius = f->getRange();
	Tile** tiles = world->getWritableTilePointersInRadius(tile, radius);

	int tileCount = (radius + 1 + radius) * (radius + 1 + radius) - 1;

	// ennyinek elégnek kéne lennie
	
	std::vector<Tile*> passable;
	passable.reserve(tileCount);

	for (int i = 0; i < tileCount; i++)
	{
		if (tiles[i] == tile)
		{
			continue;
		}
		passable.push_back(tiles[i]);
	}

	f->UpdateAreaAfterBuilding(passable.data(), tileCount);
	
	return f;
}

ServiceBuilding* Builder::BuildService(Tile* tile)
{
	if (!world->getRoadGraph()->isAdjacent(tile))
	{
		return nullptr;
	}

	ServiceBuilding* sv = world->addServBuilding(tile);
	tile->building = nullptr;
	tile->building += world->getServBuildings()->size() - 1;
	tile->texId = 23 + 3;
	tile->type = 3;
	return sv;
}
