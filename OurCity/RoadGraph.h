#ifndef ROADGRAPH_H
#define ROADGRAPH_H

#include "Road.h"
#include <vector>

class RoadGraph
{
private: 
	std::vector<Road*> roads;
	std::vector<std::vector<char>> adjMatrix;

public:
	RoadGraph();
	~RoadGraph();

	bool addRoad(Tile* tile);
	bool removeRoad(Tile* tile);
	Road* getRoadByCoords(int i, int j);
	bool checkConnectedWithout(Tile* tile);
	
	void printGraph();
	std::vector<Road*> shortestPath(Road* from, Road* to);
};

#endif
