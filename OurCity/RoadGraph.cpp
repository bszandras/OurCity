#include "RoadGraph.h"
#include <algorithm>

RoadGraph::RoadGraph()
{
}

RoadGraph::~RoadGraph()
{
    // T�rli (destruktort h�v) az �sszes utat a roads vektorb�l
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
/// V�grehajtja a sz�ks�ges ellen�rz�seket, majd ha lehet akkor hozz�adja az �j utat a gr�fhoz.
/// </summary>
/// <param name="tile">A tile, amelyikre az utat akarjuk rakni</param>
/// <param name="state">A gameState</param>
/// <returns>true, ha sikeres az �t lerak�s. false, ha sikeretlen</returns>
bool RoadGraph::addRoad(Tile* tile, GameState* state)
{
    // Ha a i vagy j koordin�ta 0, akkor nem engedj�k lerakni az utat.
    if (tile->rect.i == 0 || tile->rect.j == 0)
    {
		//std::cout << "Road has coordinate i or j = 0" << std::endl;
		return false;
	}

    // Ha m�r l�tezik �t a koordin�t�kon, akkor nem enged�nk lerakni �j utat.
    if (searchRoadByCoords(tile->rect.i, tile->rect.j))
    {
        //std::cout << "Road already exists" << std::endl;
        return false;
    }

    // Ha m�g nincs egyetlen �t sem a gr�fban, hozz�adjuk az els�t.
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

    // Ha a gr�fban m�r van �t, akkor ellen�rizz�k, hogy a lerakni k�v�nt �t szomsz�dos-e valamelyikkel.
    if (!isAdjacent(tile))
    {
        //std::cout << "Road is not adjacent to any other road" << std::endl;
        return false;
    }

    // Ha a gr�fban m�r van �t, �s a lerakni k�v�nt �t szomsz�dos legal�bb egy m�sik �ttal,
    // akkor hozz�adjuk az �j utat a gr�fhoz.
    Road* road = new Road(tile);

    // Ha a j�t�kosnak nincs el�g p�nze �j �t �p�t�s�re, akkor elutas�tjuk
    if (!state->hasEnough(road->getBuildCost()))
    {
        //std::cout << "Not enough money for road" << std::endl;
        delete road;
        return false;
    }

    // Ellenkez� esetben levonjuk a p�nzt, �s hozz�adjuk az �j utat a gr�fhoz
    state->spendMoney(road->getBuildCost());
    state->addTransaction("Road built: ", -road->getBuildCost());
    state->addToMaintenance(road->getMaintenanceCost());

    tile->building = road;
    roads.push_back(road);
    adjList.push_back(std::vector<Road*>());

    // Hozz�adjuk az �j utat a szomsz�dos utak szomsz�ds�gi list�j�hoz
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
/// V�grehajtja a sz�ks�ges ellen�rz�seket, majd
/// t�rli a param�terk�nt kapott tile-on l�v� utat a gr�fb�l.
/// </summary>
/// <param name="tile">A tile, amin a t�r�lni k�v�nt �t tal�lhat�</param>
/// <returns>true, ha sikeres a t�rl�s, false, ha nem</returns>
bool RoadGraph::removeRoad(Tile* tile)
{
    // Ellen�rizz�k, hogy a t�r�lni k�v�nt �t benne van-e a gr�fban
    if (!searchRoadByCoords(tile->rect.i, tile->rect.j))
    {
		//std::cout << "Road does not exist" << std::endl;
		return false;
	}

    Road* del = getRoadByCoords(tile->rect.i, tile->rect.j);

    // Ellen�rizz�k, hogy a t�r�lni k�v�nt �t n�lk�l a gr�f �sszef�gg� marad-e
    if (!isConnected(del))
    {
		//std::cout << "Graph is not connected" << std::endl;
		return false;
	}

    // T�r�lj�k az utat a roads vektorb�l
    for (int i = 0; i < roads.size(); i++)
    {
        if (roads[i] == del)
        {
			roads.erase(roads.begin() + i);
            //std::cout << "Road removed from roads vector" << std::endl;
			break;
		}
	}

    // T�r�lj�k az utat a szomsz�dos utak szomsz�doss�gi list�j�b�l
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

    // T�r�lj�k az utat a gr�f szomsz�doss�gi list�j�b�l
    adjList.erase(adjList.begin() + del->getId());

    // A roads vektorban normaliz�ljuk az utak indexeit.
    for (int i = del->getId(); i < roads.size(); i++)
    {
        roads[i]->setId(roads[i]->getId() - 1);
    }


    // T�r�lj�k (dekontrus�ljuk) a t�r�lt utat
    delete del;

    return true;
}

/// <summary>
/// Megn�zi, hogy a param�terk�nt kapott tile szomsz�dos-e egy �ttal.
/// </summary>
/// <param name="tile">A tile, amelyikr�l tudni szeretn�nk, hogy van-e a szomsz�ds�g�ban �t</param>
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
/// Ellen�rzi, hogy a param�terben kapott �t n�lk�l �sszef�gg� marad-e a gr�f
/// </summary>
/// <param name="road">Az �t, amelyik n�lk�l meg akarjuk n�zni, hogy �sszef�gg� marad-e a gr�f</param>
/// <returns>true, ha �sszef�gg� marad, false, ha nem</returns>
bool RoadGraph::isConnected(Road* road)
{
    // Ha a gr�f csak egyetlen utat tartalmaz, akkor �sszef�gg�
    if (roads.size() == 1)
    {
		return true;
	}

    // Ha a gr�fban t�bb �t is van, akkor n�zz�k meg, hogy �sszef�gg� marad-e az �t n�lk�l
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
/// Ellen�rzi, hogy az �t mellett van-e �p�let
/// </summary>
/// <param name="tile">A tile, amin az �t van</param>
/// <param name="neighs">Az �t szomsz�d tile-jai.</param>
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
/// Megn�zi, hogy az adott koordin�tkon tal�lhat�-e �t
/// </summary>
/// <param name="i">Az x koordin�ta</param>
/// <param name="j">Az y koordin�ta</param>
/// <returns>true, ha tal�lhat� rajta �t, false, ha nem</returns>
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
/// Visszaadja az adott koordin�t�n tal�lhat� utat
/// </summary>
/// <param name="i">Az x koordin�ta</param>
/// <param name="j">Az y koordin�ta</param>
/// <returns>Az �tra mutat� pointer, k�l�nben nullptr, ha nincs az adott koordin�t�n �t</returns>
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
/// Visszaadja az adott utat az indexe alapj�n
/// </summary>
/// <param name="index">Az �t indexe a roads vektorban</param>
/// <returns>Az �tra mutat� pointer, k�l�nben nullptr, ha nem l�tezik olyan index</returns>
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
/// K�t pont k�z�tti legr�videbb utat adja meg
/// TODO: tesztel�s
/// TODO: ha nem haszn�ljuk, akkor vegy�k ki!
/// </summary>
/// <param name="start">Az �t kezd�pontja</param>
/// <param name="end">Az �t v�gpontja</param>
/// <returns>Egy vektor, amely a legr�videbb utat tartalmazza, Road pointerek form�j�ban. </returns>
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
/// Ki�rja a konzolra a gr�fot.
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
