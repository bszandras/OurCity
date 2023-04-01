#include "RoadGraph.h"

RoadGraph::RoadGraph()
{
}

RoadGraph::~RoadGraph()
{
    // Deleting all the roads in the roads vector
    for (int i = 0; i < roads.size(); i++)
    {
		delete roads[i];
    }
}

// Copy constructor
RoadGraph::RoadGraph(RoadGraph& t)
{
    // Making a deep copy of the roads vector
    for (int i = 0; i < t.roads.size(); i++)
    {
		roads.push_back(new Road(*t.roads[i]));
	}

    // Making a deep copy of the adjList vector
    for (int i = 0; i < t.adjList.size(); i++)
    {
		std::vector<Road*> temp;
        for (int j = 0; j < t.adjList[i].size(); j++)
        {
			temp.push_back(new Road(*t.adjList[i][j]));
		}
		adjList.push_back(temp);
	}
}

bool RoadGraph::addRoad(Tile* tile)
{
    // If a road with the same coordinates already exists, return false
    if (searchRoadByCoords(tile->i, tile->j)) return false;
}

bool RoadGraph::removeRoad(Tile* tile)
{
    return false;
}

bool RoadGraph::searchRoadByCoords(int i, int j)
{
    for (size_t k = 0; k < roads.size(); k++)
    {
        if (roads[k]->getTile()->i == i && roads[k]->getTile()->j == j)
        {
            return true;
        }
    }
    return false;
}

Road* RoadGraph::getRoadByCoords(int i, int j)
{
    for (size_t k = 0; k < roads.size(); k++)
    {
        if (roads[k]->getTile()->i == i && roads[k]->getTile()->j == j)
        {
            return roads[k];
        }
    }
    return nullptr;
}

Road* RoadGraph::getRoadByIndex(int index)
{
    for (size_t k = 0; k < roads.size(); k++)
    {
        if (roads[k]->getId() == index)
        {
            return roads[k];
        }
    }
}

std::vector<Road*> RoadGraph::shortestPath(Road* start, Road* end)
{
    return std::vector<Road*>();
}

void RoadGraph::printGraph()
{
}
