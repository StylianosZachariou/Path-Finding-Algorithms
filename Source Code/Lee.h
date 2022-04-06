#pragma once
#include "Grid.h"
#include <forward_list>

//Class Responsible for Perfoming the Lee algorithm
class Lee
{
public:

	bool findPath(Grid& grid); //Lee

protected:

	bool distGrid(Grid& grid); //Fill Grid With Distances

	//The shortest path
	std::forward_list<Coords> path;

	//Coords for Neighbouring Cells
	int neighboursX[4] = { 1,  0, -1, 0 };
	int neighboursY[4] = { 0, -1,  0, 1 };
};

