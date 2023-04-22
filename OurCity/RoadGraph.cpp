#include "RoadGraph.h"
#include <algorithm>

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

bool RoadGraph::addRoad(Tile* tile, GameState* state)
{
    // If the road to add has coordinate i or j = 0 return false
    if (tile->rect.i == 0 || tile->rect.j == 0)
    {
		std::cout << "Road has coordinate i or j = 0" << std::endl;
		return false;
	}

    // If a road with the same coordinates already exists, return false
    if (searchRoadByCoords(tile->rect.i, tile->rect.j))
    {
        std::cout << "Road already exists" << std::endl;
        return false;
    }

    // If the the graph does not contain any roads, add the first road
    if (roads.size() == 0)
    {
		Road* road = new Road(tile);
        if (!state->hasEnough(road->getBuildCost()))
        {
            std::cout << "Not enough money for road" << std::endl;
            delete road;
            return false;
        }
        state->spendMoney(road->getBuildCost());
        tile->building = road;

		roads.push_back(road);
		adjList.push_back(std::vector<Road*>());
		return true;
	}

    // If the graph contains road and the new road is not adjacent to any other road, return false
    if (!isAdjacent(tile))
    {
        std::cout << "Road is not adjacent to any other road" << std::endl;
        return false;
    }

    // If the graph contains roads and the new road is adjacent to at least one other road, add the new road
    Road* road = new Road(tile);

    if (!state->hasEnough(road->getBuildCost()))
    {
        std::cout << "Not enough money for road" << std::endl;
        delete road;
        return false;
    }
    state->spendMoney(road->getBuildCost());
    tile->building = road;

    roads.push_back(road);
    adjList.push_back(std::vector<Road*>());

    // Add the new road to the adjacency list of the adjacent roads
    Road* topLeft = getRoadByCoords(tile->rect.i-1, tile->rect.j+1);
    Road* topRight = getRoadByCoords(tile->rect.i, tile->rect.j + 1);
    Road* botLeft = getRoadByCoords(tile->rect.i, tile->rect.j-1);
    Road* botRight = getRoadByCoords(tile->rect.i + 1, tile->rect.j-1);

    if (topLeft)
    {
		adjList[topLeft->getId()].push_back(road);
		adjList[road->getId()].push_back(topLeft);
	}

    if (topRight)
    {
		adjList[topRight->getId()].push_back(road);
		adjList[road->getId()].push_back(topRight);
	}

	if (botLeft)
    {
		adjList[botLeft->getId()].push_back(road);
		adjList[road->getId()].push_back(botLeft);
	}

	if (botRight)
    {
		adjList[botRight->getId()].push_back(road);
		adjList[road->getId()].push_back(botRight);
	}

	return true;
}

// TODO: Ha 2 vagy annál több út van, akkor nem engedi kitörölni a (0)-s indexû utat,
// azt mondja, hogy nem kapcsolódik a gráf
bool RoadGraph::removeRoad(Tile* tile)
{
    // Check if the road to remove is in the graph
    if (!searchRoadByCoords(tile->rect.i, tile->rect.j))
    {
		std::cout << "Road does not exist" << std::endl;
		return false;
	}

    Road* del = getRoadByCoords(tile->rect.i, tile->rect.j);
    // Check if the graph still connected after removing the road
    if (!isConnected(del))
    {
		std::cout << "Graph is not connected" << std::endl;
		return false;
	}

    // Remove the road from the roads vector
    for (int i = 0; i < roads.size(); i++)
    {
        if (roads[i] == del)
        {
			roads.erase(roads.begin() + i);
            std::cout << "Road removed from roads vector" << std::endl;
			break;
		}
	}

	// Remove the road from the adjacency list of the adjacent roads
    Road* topLeft = getRoadByCoords(tile->rect.i - 1, tile->rect.j + 1);
    Road* topRight = getRoadByCoords(tile->rect.i, tile->rect.j + 1);
    Road* botLeft = getRoadByCoords(tile->rect.i, tile->rect.j - 1);
    Road* botRight = getRoadByCoords(tile->rect.i + 1, tile->rect.j - 1);

    if (topLeft)
    {
        for (int i = 0; i < adjList[topLeft->getId()].size(); i++)
        {
            if (adjList[topLeft->getId()][i] == del)
            {
				adjList[topLeft->getId()].erase(adjList[topLeft->getId()].begin() + i);
				break;
			}
		}
	}

    if (topRight)
    {
        for (int i = 0; i < adjList[topRight->getId()].size(); i++)
        {
            if (adjList[topRight->getId()][i] == del)
            {
				adjList[topRight->getId()].erase(adjList[topRight->getId()].begin() + i);
				break;
			}
		}
	}

    if (botLeft)
    {
        for (int i = 0; i < adjList[botLeft->getId()].size(); i++)
        {
            if (adjList[botLeft->getId()][i] == del)
            {
				adjList[botLeft->getId()].erase(adjList[botLeft->getId()].begin() + i);
				break;
			}
		}
	}

    if (botRight)
    {
        for (int i = 0; i < adjList[botRight->getId()].size(); i++)
        {
            if (adjList[botRight->getId()][i] == del)
            {
				adjList[botRight->getId()].erase(adjList[botRight->getId()].begin() + i);
				break;
			}
		}
	}

	// Remove the road from the adjacency list of the graph
    adjList.erase(adjList.begin() + del->getId());

    // Normalize the indexes of the roads in the roads vector
    for (int i = del->getId(); i < roads.size(); i++)
    {
        roads[i]->setId(roads[i]->getId() - 1);
    }


    // Delete the road
    delete del;

    return true;
}

bool RoadGraph::isAdjacent(Tile* tile)
{
    Road* topLeft = getRoadByCoords(tile->rect.i - 1, tile->rect.j + 1);
    Road* topRight = getRoadByCoords(tile->rect.i, tile->rect.j + 1);
    Road* botLeft = getRoadByCoords(tile->rect.i, tile->rect.j - 1);
    Road* botRight = getRoadByCoords(tile->rect.i + 1, tile->rect.j - 1);

    if (topLeft || topRight || botLeft || botRight)
    {
        return true;
    }
    return false;
}

bool RoadGraph::isConnected(Road* road)
{
    // If the graph contains only one road, it is connected
    if (roads.size() == 1)
    {
		return true;
	}

	// If the graph contains more than one road, check if the graph is connected after removing the road
	std::vector<Road*> visited;
	std::vector<Road*> stack;
	stack.push_back(roads[0]);

    while (!stack.empty())
    {
		Road* current = stack.back();
		stack.pop_back();

        if (current == road)
        {
			continue;
		}

        if (std::find(visited.begin(), visited.end(), current) == visited.end())
        {
			visited.push_back(current);
            for (size_t i = 0; i < adjList[current->getId()].size(); i++)
            {
				stack.push_back(adjList[current->getId()][i]);
			}
		}
	}

    if (visited.size() == roads.size() - 1)
    {
		return true;
	}
	return false;
}

bool RoadGraph::hasBuildingNext(Tile* tile, Tile* neighs)
{
    if ((!searchRoadByCoords(neighs[0].rect.i, neighs[0].rect.j) && neighs[0].building != nullptr)
        || (!searchRoadByCoords(neighs[1].rect.i, neighs[1].rect.j) && neighs[1].building != nullptr)
        || (!searchRoadByCoords(neighs[2].rect.i, neighs[2].rect.j) && neighs[2].building != nullptr)
        || (!searchRoadByCoords(neighs[3].rect.i, neighs[3].rect.j) && neighs[3].building != nullptr))
    {
        return true;
    }
    return false;

}

bool RoadGraph::searchRoadByCoords(int i, int j)
{
    for (size_t k = 0; k < roads.size(); k++)
    {
        if (roads[k]->getTile()->rect.i == i && roads[k]->getTile()->rect.j == j)
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
        if (roads[k]->getTile()->rect.i == i && roads[k]->getTile()->rect.j == j)
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

// TODO: test this
std::vector<Road*> RoadGraph::shortestPath(Road* start, Road* end)
{
    std::vector<Road*> path;
	std::vector<Road*> visited;
	std::vector<Road*> stack;
	std::vector<Road*> prev;
	stack.push_back(start);

    while (!stack.empty())
    {
		Road* current = stack.back();
		stack.pop_back();

        if (current == end)
        {
			break;
		}

        if (std::find(visited.begin(), visited.end(), current) == visited.end())
        {
			visited.push_back(current);
            for (size_t i = 0; i < adjList[current->getId()].size(); i++)
            {
				stack.push_back(adjList[current->getId()][i]);
				prev.push_back(current);
			}
		}
	}

	Road* current = end;
    while (current != start)
    {
		path.push_back(current);
		current = prev[current->getId()];
	}
	path.push_back(start);

	return path;
}

void RoadGraph::printGraph()
{
    for (size_t i = 0; i < adjList.size(); i++)
        {
            std::cout << i << " (" << roads[i]->getTile()->rect.i <<", " << roads[i]->getTile()->rect.j << ") " << " -> ";
            for (size_t j = 0; j < adjList[i].size(); j++)
            {
                std::cout << adjList[i][j]->getId() << " ";
            }
            std::cout << std::endl;
        }
}
