#include "RoadGraph.h"

#include <iostream>
#include <queue>

RoadGraph::RoadGraph()
{
}

RoadGraph::~RoadGraph()
{
}

bool RoadGraph::addRoad(Tile* tile)
{
	// check, if the graph is empty, if yes, we add the first road to the Graph
	if (this->roads.empty())
	{
		Road *road = new Road(tile);
		this->roads.push_back(road);

		this->adjMatrix.push_back(std::vector<char>());
		this->adjMatrix[0].push_back('0');

		return true;
	}

	// check, if the road is already in the graph
	for (int i = 0; i < this->roads.size(); i++)
	{
		if (this->roads[i]->getTile() == tile)
		{
			return false;
		}
	}

	// check if the road is connected to another road
	Road* top = this->getRoadByCoords(tile->i, tile->j - 1);
	Road* bottom = this->getRoadByCoords(tile->i, tile->j + 1);
	Road* left = this->getRoadByCoords(tile->i - 1, tile->j);
	Road* right = this->getRoadByCoords(tile->i + 1, tile->j);

	if (top != nullptr || bottom != nullptr || left != nullptr || right != nullptr)
	{
		Road *road = new Road(tile);
		this->roads.push_back(road);

		// add a new row to the adjMatrix
		this->adjMatrix.push_back(std::vector<char>());
		for (int i = 0; i < this->roads.size(); i++)
		{
			this->adjMatrix[this->roads.size() - 1].push_back('0');
		}

		// add a new column to the adjMatrix
		for (int i = 0; i < this->roads.size() - 1; i++)
		{
			this->adjMatrix[i].push_back('0');
		}

		// add the new road to the adjMatrix
		if (top != nullptr)
		{
			this->adjMatrix[this->roads.size() - 1][top->getIdx()] = '1';
			this->adjMatrix[top->getIdx()][this->roads.size() - 1] = '1';
		}
		if (bottom != nullptr)
		{
			this->adjMatrix[this->roads.size() - 1][bottom->getIdx()] = '1';
			this->adjMatrix[bottom->getIdx()][this->roads.size() - 1] = '1';
		}
		if (left != nullptr)
		{
			this->adjMatrix[this->roads.size() - 1][left->getIdx()] = '1';
			this->adjMatrix[left->getIdx()][this->roads.size() - 1] = '1';
		}
		if (right != nullptr)
		{
			this->adjMatrix[this->roads.size() - 1][right->getIdx()] = '1';
			this->adjMatrix[right->getIdx()][this->roads.size() - 1] = '1';
		}

		return true;
	}
	else
	{
		return false;
	}
}

bool RoadGraph::removeRoad(Tile* tile)
{
	// search for the Road to be deleted
	Road* del = getRoadByCoords(tile->i, tile->j);

	if (del)
	{

	}
}

Road* RoadGraph::getRoadByCoords(int i, int j)
{
	for (int i = 0; i < this->roads.size(); i++)
	{
		if (this->roads[i]->getTile()->i == i && this->roads[i]->getTile()->j == j)
		{
			return roads[i];
		}
	}
	return nullptr;
}

bool RoadGraph::checkConnectedWithout(Road* road)
{

}