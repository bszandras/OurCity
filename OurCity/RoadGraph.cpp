#include "RoadGraph.h"
#include <algorithm>

RoadGraph::RoadGraph()
{
}

RoadGraph::~RoadGraph()
{
    // Törli (destruktort hív) az összes utat a roads vektorból
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

/// <summary>
/// Végrehajtja a szükséges ellenõrzéseket, majd ha lehet akkor hozzáadja az új utat a gráfhoz.
/// </summary>
/// <param name="tile">A tile, amelyikre az utat akarjuk rakni</param>
/// <param name="state">A gameState</param>
/// <returns>true, ha sikeres az út lerakás. false, ha sikeretlen</returns>
bool RoadGraph::addRoad(Tile* tile, GameState* state)
{
    // Ha a i vagy j koordináta 0, akkor nem engedjük lerakni az utat.
    if (tile->rect.i == 0 || tile->rect.j == 0)
    {
		//std::cout << "Road has coordinate i or j = 0" << std::endl;
		return false;
	}

    // Ha már létezik út a koordinátákon, akkor nem engedünk lerakni új utat.
    if (searchRoadByCoords(tile->rect.i, tile->rect.j))
    {
        //std::cout << "Road already exists" << std::endl;
        return false;
    }

    // Ha még nincs egyetlen út sem a gráfban, hozzáadjuk az elsõt.
    if (roads.size() == 0)
    {
		Road* road = new Road(tile);
        if (!state->hasEnough(road->getBuildCost()))
        {
            //std::cout << "Not enough money for road" << std::endl;
            delete road;
            return false;
        }
        state->spendMoney(road->getBuildCost());
        state->addTransaction("Road built: ", -road->getBuildCost());
        state->addToMaintenance(road->getMaintenanceCost());
        tile->building = road;

		roads.push_back(road);
		adjList.push_back(std::vector<Road*>());
		return true;
	}

    // Ha a gráfban már van út, akkor ellenõrizzük, hogy a lerakni kívánt út szomszédos-e valamelyikkel.
    if (!isAdjacent(tile))
    {
        //std::cout << "Road is not adjacent to any other road" << std::endl;
        return false;
    }

    // Ha a gráfban már van út, és a lerakni kívánt út szomszédos legalább egy másik úttal,
    // akkor hozzáadjuk az új utat a gráfhoz.
    Road* road = new Road(tile);

    // Ha a játékosnak nincs elég pénze új út építésére, akkor elutasítjuk
    if (!state->hasEnough(road->getBuildCost()))
    {
        //std::cout << "Not enough money for road" << std::endl;
        delete road;
        return false;
    }

    // Ellenkezõ esetben levonjuk a pénzt, és hozzáadjuk az új utat a gráfhoz
    state->spendMoney(road->getBuildCost());
    state->addTransaction("Road built: ", -road->getBuildCost());
    state->addToMaintenance(road->getMaintenanceCost());

    tile->building = road;
    roads.push_back(road);
    adjList.push_back(std::vector<Road*>());

    // Hozzáadjuk az új utat a szomszédos utak szomszédsági listájához
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

/// <summary>
/// Végrehajtja a szükséges ellenõrzéseket, majd
/// törli a paraméterként kapott tile-on lévõ utat a gráfból.
/// </summary>
/// <param name="tile">A tile, amin a törölni kívánt út található</param>
/// <returns>true, ha sikeres a törlés, false, ha nem</returns>
bool RoadGraph::removeRoad(Tile* tile)
{
    // Ellenõrizzük, hogy a törölni kívánt út benne van-e a gráfban
    if (!searchRoadByCoords(tile->rect.i, tile->rect.j))
    {
		//std::cout << "Road does not exist" << std::endl;
		return false;
	}

    Road* del = getRoadByCoords(tile->rect.i, tile->rect.j);

    // Ellenõrizzük, hogy a törölni kívánt út nélkül a gráf összefüggõ marad-e
    if (!isConnected(del))
    {
		//std::cout << "Graph is not connected" << std::endl;
		return false;
	}

    // Töröljük az utat a roads vektorból
    for (int i = 0; i < roads.size(); i++)
    {
        if (roads[i] == del)
        {
			roads.erase(roads.begin() + i);
            //std::cout << "Road removed from roads vector" << std::endl;
			break;
		}
	}

    // Töröljük az utat a szomszédos utak szomszédossági listájából
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

    // Töröljük az utat a gráf szomszédossági listájából
    adjList.erase(adjList.begin() + del->getId());

    // A roads vektorban normalizáljuk az utak indexeit.
    for (int i = del->getId(); i < roads.size(); i++)
    {
        roads[i]->setId(roads[i]->getId() - 1);
    }


    // Töröljük (dekontrusáljuk) a törölt utat
    delete del;

    return true;
}

/// <summary>
/// Megnézi, hogy a paraméterként kapott tile szomszédos-e egy úttal.
/// </summary>
/// <param name="tile">A tile, amelyikrõl tudni szeretnénk, hogy van-e a szomszédságában út</param>
/// <returns>true, ha van, false, ha nincs</returns>
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

/// <summary>
/// Ellenõrzi, hogy a paraméterben kapott út nélkül összefüggõ marad-e a gráf
/// </summary>
/// <param name="road">Az út, amelyik nélkül meg akarjuk nézni, hogy összefüggõ marad-e a gráf</param>
/// <returns>true, ha összefüggõ marad, false, ha nem</returns>
bool RoadGraph::isConnected(Road* road)
{
    // Ha a gráf csak egyetlen utat tartalmaz, akkor összefüggõ
    if (roads.size() == 1)
    {
		return true;
	}

    // Ha a gráfban több út is van, akkor nézzük meg, hogy összefüggõ marad-e az út nélkül
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


/// <summary>
/// Ellenõrzi, hogy az út mellett van-e épület
/// </summary>
/// <param name="tile">A tile, amin az út van</param>
/// <param name="neighs">Az út szomszéd tile-jai.</param>
/// <returns>true, ha van false, ha nincs</returns>
bool RoadGraph::hasBuildingNext(Tile* tile, Tile** neighs)
{
    if ((!searchRoadByCoords(neighs[0]->rect.i, neighs[0]->rect.j) && (neighs[0]->building != nullptr || neighs[0]->type != 0))
        || (!searchRoadByCoords(neighs[1]->rect.i, neighs[1]->rect.j) && (neighs[1]->building != nullptr || neighs[1]->type != 0))
        || (!searchRoadByCoords(neighs[2]->rect.i, neighs[2]->rect.j) && (neighs[2]->building != nullptr || neighs[2]->type != 0))
        || (!searchRoadByCoords(neighs[3]->rect.i, neighs[3]->rect.j) && (neighs[3]->building != nullptr || neighs[3]->type != 0)))
    {
        return true;
    }
    return false;

}

/// <summary>
/// Megnézi, hogy az adott koordinátkon található-e út
/// </summary>
/// <param name="i">Az x koordináta</param>
/// <param name="j">Az y koordináta</param>
/// <returns>true, ha található rajta út, false, ha nem</returns>
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

/// <summary>
/// Visszaadja az adott koordinátán található utat
/// </summary>
/// <param name="i">Az x koordináta</param>
/// <param name="j">Az y koordináta</param>
/// <returns>Az útra mutató pointer, különben nullptr, ha nincs az adott koordinátán út</returns>
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

/// <summary>
/// Visszaadja az adott utat az indexe alapján
/// </summary>
/// <param name="index">Az út indexe a roads vektorban</param>
/// <returns>Az útra mutató pointer, különben nullptr, ha nem létezik olyan index</returns>
Road* RoadGraph::getRoadByIndex(int index)
{
    for (size_t k = 0; k < roads.size(); k++)
    {
        if (roads[k]->getId() == index)
        {
            return roads[k];
        }
    }
    return nullptr;
}

/// <summary>
/// Két pont közötti legrövidebb utat adja meg
/// TODO: tesztelés
/// TODO: ha nem használjuk, akkor vegyük ki!
/// </summary>
/// <param name="start">Az út kezdõpontja</param>
/// <param name="end">Az út végpontja</param>
/// <returns>Egy vektor, amely a legrövidebb utat tartalmazza, Road pointerek formájában. </returns>
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

/// <summary>
/// Kiírja a konzolra a gráfot.
/// </summary>
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
