#ifndef ROADGRAPH_H
#define ROADGRAPH_H

#include <vector>
#include <iostream>
#include "Road.h"

class RoadGraph
{
private:
	std::vector<Road*> roads;
	std::vector<std::vector<Road*>> adjList;

public:
	RoadGraph();
	~RoadGraph();
	RoadGraph(RoadGraph& t);

	bool addRoad(Tile* tile);
	bool removeRoad(Tile* tile);
	bool isAdjacent(Tile* tile);

	bool searchRoadByCoords(int i, int j);
	
	Road* getRoadByCoords(int i, int j);
	Road* getRoadByIndex(int index);

	std::vector<Road*> shortestPath(Road* start, Road* end);
	void printGraph();
};

#endif