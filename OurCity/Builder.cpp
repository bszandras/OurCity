#include "Builder.h"

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
		// a tile-hoz utat kötést a gráf oldja meg és a pénz checket is
		if (world->AddRoad(wrapper->GetRectsById(&where, 1), scene))
		{
			wrapper->UpdateTexIdById(where, 14);
			if (currentlyHighlighted == where)
			{
				currentTex = 14;
			}
		}
		
		break;
	default:
		break;
	}

	//primaryState = BuilderState::NOBUILD;
	//secondaryState = BuilderSubState::NONE;
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

	//ide kell egy check, hogy ha túl kicsi a távolság a két sarok között akkor return-öljön

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
