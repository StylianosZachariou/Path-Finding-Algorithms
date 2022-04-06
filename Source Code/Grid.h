#pragma once
#include <stdlib.h>     
#include <time.h>       
#include <vector>

//Coordinates Float Structure
struct Coordsf
{
	float x, y;
};

//Coordinates Integer Structure
struct Coords
{
	int x, y;
};

//Cells Structures
struct Cells
{
	Cells* parent=nullptr;
	int gcost, fcost, hcost;
	int value;
	Coords coords;
};

//Grid Class
class Grid
{
public:
	Grid();

	//Update Grid
	void updateGrid(int rows, int columns);

	//Reset Grid
	void resetGrid();
	
	//Fill Grid With Random Walls
	void randomWalls();

	//Width and Height of Grid
	int width;
	int height;

	//The Grid
	std::vector<std::vector<Cells>> grid;

	//The Start and End of the path
	Coords start = { -1,-1 };
	Coords end = { -1,-1 };
};

