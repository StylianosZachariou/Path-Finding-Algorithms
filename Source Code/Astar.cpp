#include "Astar.h"

//Heuristics
int Astar::heuristic(Cells current, Cells end, Grid& grid)
{
	//Euclidean Distance Algorithm
	float dx = abs(current.coords.x - end.coords.x);
	float dy = abs(current.coords.y - end.coords.y);
	return sqrt(dx * dx + dy * dy);
}

//The distance between two cells
int Astar::distBetween(Cells current, Cells node, Grid& grid)
{
	if (current.coords.x != node.coords.x && current.coords.y != node.coords.y) //If the cell is diagonal to the current cell
	{
		return 15; //distance is 15
	}
	else 
	{
		return 10; //distance is 10
	}
}

//Perform the A* algorithm
bool Astar::findPath(Grid& grid)
{
	//Clear Both Sets
	openSet.clear();
	closedSet.clear();
	
	//Initialize the Start Cell
	grid.grid[grid.start.x][grid.start.y].gcost = 0;
	grid.grid[grid.start.x][grid.start.y].fcost = grid.grid[grid.start.x][grid.start.y].gcost + heuristic(grid.grid[grid.start.x][grid.start.y], grid.grid[grid.end.x][grid.end.y],grid);
	grid.grid[grid.start.x][grid.start.y].parent = nullptr;

	Cells* current = &grid.grid[grid.start.x][grid.start.y]; //Current Cell is Starting Cell
	Cells* cell = nullptr;

	openSet.insert(current); //Insert Starting Cell in Open Set

	//Loop until OpenSet is Empty
	while (!openSet.empty())
	{
		current = *openSet.begin(); //Current points to the firts element in the openSet

		//Loop through all elements in open set
		for (auto c : openSet)
		{
			if (c->fcost < current->fcost) //If the fcost of c is smaller than the current's 
			{
				current = c; //current becomes c
			}
		}

		//If current is the end cell
		if (current->coords.x == grid.end.x && current->coords.y == grid.end.y)
		{
			//stop
			break;
		}

		openSet.erase(openSet.find(current)); //Remove from openSet current
		closedSet.insert(current); //Insert it into the closed set

		//Loop for all the current's neighbours
		for (int i = 0; i < 8; i++)
		{
			int x = current->coords.x + neighboursX[i]; //X coords of the current neighboure
			int y = current->coords.y + neighboursY[i]; //Y coords of the current neighboure

			//If neighboure is not of the edge
			if ((x >= 0 && x <= grid.width-1) && (y >= 0 && y <= grid.height-1))
			{

				cell = &grid.grid[x][y];//neighbour

				if (cell->value !=-2)//if its not a wall
				{

					if (closedSet.find(cell) != closedSet.end())//If cell is in the closed set
					{
						continue;//skip
					}

					int new_g = current->gcost + distBetween(*current, *cell,grid);//Calculate g cost for this cell

					if (openSet.find(cell) == openSet.end()) //If cell is not in the open set
					{
						openSet.insert(cell);//insert it
					}
					else //ELSE
					{
						if (new_g >= cell->gcost)//if the new gcost is more than the one it had already
						{
							continue;//skip
						}
					}

					//Assign gcost, hcost, fcost, parent for the cell
					grid.grid[cell->coords.x][cell->coords.y].gcost = new_g;
					grid.grid[cell->coords.x][cell->coords.y].hcost = heuristic(*cell, grid.grid[grid.end.x][grid.end.y],grid);
					grid.grid[cell->coords.x][cell->coords.y].fcost = cell->gcost + cell->hcost;
					grid.grid[cell->coords.x][cell->coords.y].parent = &grid.grid[current->coords.x][current->coords.y];
				}
			}
		}
	}
	
	Coords currentNode = grid.grid[grid.end.x][grid.end.y].coords; //Current Node is the end 

	if (grid.grid[grid.end.x][grid.end.y].parent == nullptr) //if the parent is nullptr
	{
		return false; //no path is found
	}
	else
	{
		//Path Available
		while (currentNode.x != grid.start.x || currentNode.y != grid.start.y) //Loop until start cell is found
		{
			grid.grid[currentNode.x][currentNode.y].value = 0; //change value of cell to 0 (for display purposes)
			currentNode = grid.grid[currentNode.x][currentNode.y].parent->coords; //current node becomes the parent of the current node
		}
		return true; //Path found
	}
}