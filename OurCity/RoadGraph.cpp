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
    // If the road to add has coordinate i or j = 0 return false
    if (tile->i == 0 || tile->j == 0)
    {
		std::cout << "Road has coordinate i or j = 0" << std::endl;
		return false;
	}

    // If a road with the same coordinates already exists, return false
    if (searchRoadByCoords(tile->i, tile->j))
    {
        std::cout << "Road already exists" << std::endl;
        return false;
    }

    // If the the graph does not contain any roads, add the first road
    if (roads.size() == 0)
    {
		Road* road = new Road(tile);
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

// TODO: Ha 2 vagy annál több út van, akkor nem engedi kitörölni a (0)-s indexû utat,
// azt mondja, hogy nem kapcsolódik a gráf
bool RoadGraph::removeRoad(Tile* tile)
{
    // Check if the road to remove is in the graph
    if (!searchRoadByCoords(tile->i, tile->j))
    {
		std::cout << "Road does not exist" << std::endl;
		return false;
	}

    Road* del = getRoadByCoords(tile->i, tile->j);
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
	Road* top = getRoadByCoords(tile->i, tile->j - 1);
	Road* bottom = getRoadByCoords(tile->i, tile->j + 1);
	Road* left = getRoadByCoords(tile->i - 1, tile->j);
	Road* right = getRoadByCoords(tile->i + 1, tile->j);

    if (top)
    {
        for (int i = 0; i < adjList[top->getId()].size(); i++)
        {
            if (adjList[top->getId()][i] == del)
            {
				adjList[top->getId()].erase(adjList[top->getId()].begin() + i);
				break;
			}
		}
	}

    if (bottom)
    {
        for (int i = 0; i < adjList[bottom->getId()].size(); i++)
        {
            if (adjList[bottom->getId()][i] == del)
            {
				adjList[bottom->getId()].erase(adjList[bottom->getId()].begin() + i);
				break;
			}
		}
	}

    if (left)
    {
        for (int i = 0; i < adjList[left->getId()].size(); i++)
        {
            if (adjList[left->getId()][i] == del)
            {
				adjList[left->getId()].erase(adjList[left->getId()].begin() + i);
				break;
			}
		}
	}

    if (right)
    {
        for (int i = 0; i < adjList[right->getId()].size(); i++)
        {
            if (adjList[right->getId()][i] == del)
            {
				adjList[right->getId()].erase(adjList[right->getId()].begin() + i);
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
            std::cout << i << " (" << roads[i]->getTile()->i <<", " << roads[i]->getTile()->j << ") " << " -> ";
            for (size_t j = 0; j < adjList[i].size(); j++)
            {
                std::cout << adjList[i][j]->getId() << " ";
            }
            std::cout << std::endl;
        }
}
