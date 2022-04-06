#pragma once
#include "Grid.h"
#include <unordered_set>
//Class Responsible for perfoming the A* algorithm
class Astar
{
public:
	bool findPath(Grid& grid); //A*
protected:

	int heuristic(Cells current, Cells end,Grid& grid); //Heuristics
	int distBetween(Cells current, Cells node,Grid& grid); //Distane Between 2 points

	std::unordered_set<Cells*> openSet, closedSet; //Open and Close Set

	//Coords For Neighbouring Cells
	int neighboursX[8] = { 1,  1,  0, -1, -1, -1, 0, 1 };
	int neighboursY[8] = { 0, -1, -1, -1,  0,  1, 1, 1 };
};

