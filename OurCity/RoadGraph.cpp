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

    // If the the graph does not contain any roads, add the first road
    if (roads.size() == 0)
    {
		Road* road = new Road(tile);
		roads.push_back(road);
		adjList.push_back(std::vector<Road*>());
		return true;
	}

    // If the graph contains road and the new road is not adjacent to any other road, return false
    if (!isAdjacent(tile)) return false;

    // If the graph contains roads and the new road is adjacent to at least one other road, add the new road
    Road* road = new Road(tile);
    roads.push_back(road);
    adjList.push_back(std::vector<Road*>());

    // Add the new road to the adjacency list of the adjacent roads
    Road* top = getRoadByCoords(tile->i, tile->j - 1);
    Road* bottom = getRoadByCoords(tile->i, tile->j + 1);
    Road* left = getRoadByCoords(tile->i - 1, tile->j);
    Road* right = getRoadByCoords(tile->i + 1, tile->j);

    if (top)
    {
		adjList[top->getId()].push_back(road);
		adjList[road->getId()].push_back(top);
	}

    if (bottom)
    {
		adjList[bottom->getId()].push_back(road);
		adjList[road->getId()].push_back(bottom);
	}

	if (left)
    {
		adjList[left->getId()].push_back(road);
		adjList[road->getId()].push_back(left);
	}

	if (right)
    {
		adjList[right->getId()].push_back(road);
		adjList[road->getId()].push_back(right);
	}

	return true;
}

bool RoadGraph::removeRoad(Tile* tile)
{
    return false;
}

bool RoadGraph::isAdjacent(Tile* tile)
{
    Road* top = getRoadByCoords(tile->i, tile->j - 1);
    Road* bottom = getRoadByCoords(tile->i, tile->j + 1);
    Road* left = getRoadByCoords(tile->i - 1, tile->j);
    Road* right = getRoadByCoords(tile->i + 1, tile->j);

    if (top || bottom || left || right)
    {
        return true;
    }
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
    for (size_t i = 0; i < adjList.size(); i++)
        {
            std::cout << i << " -> ";
            for (size_t j = 0; j < adjList[i].size(); j++)
            {
                std::cout << adjList[i][j]->getId() << " ";
            }
            std::cout << std::endl;
        }
}
