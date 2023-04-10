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
}
void Builder::BuildSpecBuilding(int where)
{
	Tile* tile = wrapper->GetPointerToId(where);
	if (tile->hasZone || tile->building != nullptr)
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
		Tile* tile = wrapper->GetPointerToId(where);
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
		Tile* tile = wrapper->GetPointerToId(where);
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
		std::cout << "not enough money for <-building->" << std::endl;
		return false;
	}

	wrapper->GetPointerToId(where)->building = building;

	wrapper->UpdateTexIdById(where, tex);
	if (currentlyHighlighted == where)
	{
		currentTex = tex;
	}

	return true;
}
bool Builder::DestroySpecBuilding(int where)
{
	Tile* tile = wrapper->GetPointerToId(where);
	if (tile->building == nullptr)
	{
		std::cout << "there is nothing here to destroy" << std::endl;
		return false;
	}

	Building* b = tile->building;
	wrapper->GetPointerToId(where)->building = nullptr;

	// TODO
	// ide fognak kerülni a spec épület update-ek

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
	if (tile->building != nullptr)
	{
		return;
	}

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
				// wrapper->UpdateTexIdById(where, 2);

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
				return;
			}
		}
	}
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
