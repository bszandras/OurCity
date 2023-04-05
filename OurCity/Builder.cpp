#include "Builder.h"
#include "BuildingsInclude.h"

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
		wrapper->UpdateTexIdById(currentlyHighlighted, currentTex);
	}
}

void Builder::Build(int where)
{
	switch (primaryState)
	{
	case NOBUILD:
		return;
		break;
	case ZONE:
		SelectZone();
		break;
	case ZONECANCEL:
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
}
void Builder::BuildSpecBuilding(int where)
{
	switch (secondaryState)
	{
	case ROAD:
		// a tile-hoz utat k�t�st a gr�f oldja meg �s a p�nz checket is
		if (world->AddRoad(wrapper->GetRectsById(&where, 1), scene))
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
		Tile* tile = wrapper->GetRectsById(&where, 1);
		if (world->getRoadGraph()->isAdjacent(tile))
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
		Tile* tile = wrapper->GetRectsById(&where, 1);
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
		Tile* tile = wrapper->GetRectsById(&where, 1);
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
		Tile* tile = wrapper->GetRectsById(&where, 1);
		if (world->getRoadGraph()->isAdjacent(tile))
		{
			HighSchool* build = new HighSchool(tile);
			bool succ = BuildSpecBuilding(tile, build, where, HIGHSCHOOL);

			if (!succ)
			{
				delete build;
			}
		}
		break;
	}
	case UNIVERSITY:
	{
		Tile* tile = wrapper->GetRectsById(&where, 1);
		if (world->getRoadGraph()->isAdjacent(tile))
		{
			University* build = new University(tile);
			bool succ = BuildSpecBuilding(tile, build, where, UNIVERSITY);

			if (!succ)
			{
				delete build;
			}
		}
		break;
	}
	case STADIUM:
	{
		Tile* tile = wrapper->GetRectsById(&where, 1);
		if (world->getRoadGraph()->isAdjacent(tile))
		{
			Stadium* build = new Stadium(tile);
			bool succ = BuildSpecBuilding(tile, build, where, STADIUM);

			if (!succ)
			{
				delete build;
			}
		}
		break;
	}
	default:
		break;
	}

	//primaryState = BuilderState::NOBUILD;
	//secondaryState = BuilderSubState::NONE;
}
bool Builder::BuildSpecBuilding(Tile* tile, Building* building, int where, int tex)
{
	//FireStation* fire = new FireStation(tile);
	if (tile->building != nullptr)
	{
		std::cout << "there is a building already here" << std::endl;
		return false;
	}

	if (!scene->getGameState()->hasEnough(building->getBuildCost()))
	{
		std::cout << "not enough money for <-building->" << std::endl;
		return false;
	}

	wrapper->SetBuilding(where, building);
	//tile->building = building;

	wrapper->UpdateTexIdById(where, tex);
	if (currentlyHighlighted == where)
	{
		currentTex = tex;
	}

	return true;
}
bool Builder::DestroySpecBuilding(int where)
{
	Tile* tile = wrapper->GetRectsById(&where, 1);
	if (tile->building == nullptr)
	{
		std::cout << "there is nothing here to destroy" << std::endl;
		return false;
	}

	Building* b = tile->building;
	//tile->building = nullptr;
	wrapper->SetBuilding(where, nullptr);

	// TODO
	// ide fognak ker�lni a spec �p�let update-ek

	scene->getGameState()->income(b->getBuildCost() / 2);
	delete b;

	wrapper->UpdateTexIdById(where, 2);
	if (currentlyHighlighted == where)
	{
		currentTex = 2;
	}
	return true;
}
void Builder::SelectZone()
{
	// debug 0,0-b�l indul a zone highlight
	switch (secondaryState)
	{
	case NONE:
		std::cout << "something went fucky wucky" << std::endl;
		return;
		break;
	case HOUSINGZONE:
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 11);

			// create zone and push tile into it
			Zone zone(0);
			zone.addTile(areaHighlightedIds[i]);
			world->addHouseZone(zone);
		}
		break;
	case INDUSTRIALZONE:
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 12);

			// create zone and push tile into it
			Zone zone(1);
			zone.addTile(areaHighlightedIds[i]);
			world->addIndustryZone(zone);
		}
		break;
	case SERVICEZONE:
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 13);

			// create zone and push tile into it
			Zone zone(2);
			zone.addTile(areaHighlightedIds[i]);
			world->addServiceZone(zone);
		}
		break;
	default:
		std::cout << "something went fucky wucky" << std::endl;
		return;
		break;
	}
	currentlyHighlighted = 0;
	currentTex = 0;
	areaHighlightedIds.clear();
	areaHighlightedTexes.clear();
	//primaryState = BuilderState::NOBUILD;
	//secondaryState = BuilderSubState::NONE;
}



void Builder::Highlight(int target)
{
	// unhighlight previous highlight
	wrapper->UpdateTexIdById(currentlyHighlighted, currentTex);

	if (primaryState == NOBUILD)
	{
		return;
	}

	// store current highlight data
	currentlyHighlighted = target;
	currentTex = wrapper->GetRectsById(&target, 1)->texId;

	// new highlight
	// buildstate dependant highlighting is possible here
	wrapper->UpdateTexIdById(target, 10);
}

void Builder::HighlightArea(Vector2Data mouseWorldPosition, World* world)
{
	if (primaryState != BuilderState::ZONE)
	{
		return;
	}

	Vector2Data corner1 = mouse->getWorldDragStart();
	Vector2Data corner2 = mouseWorldPosition;

	//ide kell egy check, hogy ha t�l kicsi a t�vols�g a k�t sarok k�z�tt akkor return-�lj�n

	UnHighlightArea();

	std::vector<int> ids;
	ids = world->tileIdsInArea(corner1, corner2);
	/*
	if (corner1.x < corner2.x)
	{
		ids = world->tileIdsInArea(corner1, corner2);
	}
	else
	{
		ids = world->tileIdsInArea(corner2, corner1);
	}
	*/

	for (int i = 0; i < ids.size(); i++)
	{
		if (std::find(areaHighlightedIds.begin(), areaHighlightedIds.end(), ids[i]) == areaHighlightedIds.end()) {
			areaHighlightedIds.push_back(ids[i]);
			areaHighlightedTexes.push_back(world->getWrapper()->GetRectsById(&ids[i], 1)->texId);
		}
		int highlight = secondaryState;
		highlight += 10;
		world->getWrapper()->UpdateTexIdById(ids[i], highlight);
	}
}

void Builder::UnHighlightArea()
{
	if (areaHighlightedIds.size() == 0)
	{
		return;
	}

	for (int i = 0; i < areaHighlightedIds.size(); i++)
	{
		world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], areaHighlightedTexes[i]);
	}

	areaHighlightedIds.clear();
	areaHighlightedTexes.clear();
}
