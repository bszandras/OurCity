#ifndef ROADGRAPH_H
#define ROADGRAPH_H

#include <vector>
#include <iostream>
#include "Road.h"
#include "GameState.h"

class RoadGraph
{
private:
	std::vector<Road*> roads;
	std::vector<std::vector<Road*>> adjList;

public:
	RoadGraph();
	~RoadGraph();
	RoadGraph(RoadGraph& t);

	bool addRoad(Tile* tile, GameState* state);
	bool removeRoad(Tile* tile);
	bool isAdjacent(Tile* tile);
	bool isConnected(Road* road);
	bool hasBuildingNext(Tile* tile, Tile* neighs);

	bool searchRoadByCoords(int i, int j);
	
	Road* getRoadByCoords(int i, int j);
	Road* getRoadByIndex(int index);

	std::vector<Road*> shortestPath(Road* start, Road* end);
	void printGraph();
};

#endif