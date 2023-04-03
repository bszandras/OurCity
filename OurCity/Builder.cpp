#include "Builder.h"

Builder::Builder(TileRectWrapper* wrapper, MouseController* mouse, World* world)
{
	Builder::wrapper = wrapper;
	Builder::mouse = mouse;
	Builder::world = world;
}

Builder::~Builder()
{
}
void Builder::ChangeState(BuilderState state, BuilderSubState subState)
{

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
		wrapper->UpdateTexIdById(where, 1);
		world->AddRoad(wrapper->GetRectsById(&where, 1));
		if (currentlyHighlighted == where)
		{
			currentTex = 3;
		}
		break;
	default:
		break;
	}
}

void Builder::SelectZone()
{
	// debug 0,0-ból indul a zone highlight
	switch (secondaryState)
	{
	case NONE:
		return;
		break;
	case HOUSINGZONE:
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 5);

			// create zone and push tile into it
			Zone zone(0);
			zone.addTile(areaHighlightedIds[i]);
			world->addHouseZone(zone);
		}
		break;
	case INDUSTRIALZONE:
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 6);

			// create zone and push tile into it
			Zone zone(1);
			zone.addTile(areaHighlightedIds[i]);
			world->addIndustryZone(zone);
		}
		break;
	case SERVICEZONE:
		for (int i = 0; i < areaHighlightedIds.size(); i++)
		{
			world->getWrapper()->UpdateTexIdById(areaHighlightedIds[i], 7);

			// create zone and push tile into it
			Zone zone(2);
			zone.addTile(areaHighlightedIds[i]);
			world->addServiceZone(zone);
		}
		break;
	default:
		break;
	}
	currentlyHighlighted = 0;
	currentTex = 0;
	areaHighlightedIds.clear();
	areaHighlightedTexes.clear();
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
	wrapper->UpdateTexIdById(target, 1);
}

void Builder::HighlightArea(Vector2Data mouseWorldPosition, World* world)
{
	Vector2Data corner1 = mouse->getWorldDragStart();
	Vector2Data corner2 = mouseWorldPosition;

	//ide kell egy check, hogy ha túl kicsi a távolság a két sarok között akkor return-öljön

	UnHighlightArea();

	std::vector<int> ids = world->tileIdsInArea(corner1, corner2);

	for (int i = 0; i < ids.size(); i++)
	{
		if (std::find(areaHighlightedIds.begin(), areaHighlightedIds.end(), ids[i]) == areaHighlightedIds.end()) {
			areaHighlightedIds.push_back(ids[i]);
			areaHighlightedTexes.push_back(world->getWrapper()->GetRectsById(&ids[i], 1)->texId);
		}
		int highlight = secondaryState;
		highlight += 4;
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
