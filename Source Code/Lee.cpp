#include "Lee.h"

//Fill grid with distances
bool Lee::distGrid(Grid &grid)
{
	//Initialize Variables
	bool foundend = false;
	bool foundempty = true;
	int counter = 0;

	//Start Cell is 0 distance
	grid.grid[grid.start.x][grid.start.y].value = 0;

	//Loop until the end is found or there are no more empty cells
	while (!foundend && foundempty)
	{
		foundempty = false;

		for (int j = 0; j < grid.height; j++) //Loop for all rows
		{
			for (int i = 0; i < grid.width; i++) //Loop for all columns
			{
				if (grid.grid[i][j].value == counter) //If The Cells value is Equal to counter
				{
					for (int k = 0; k < 4; k++) //Loop for all neighbours
					{
						int x = grid.grid[i][j].coords.x + neighboursX[k]; //X coords for current Neighbour
						int y = grid.grid[i][j].coords.y + neighboursY[k]; //Y coords for current Neighbour

						if ((x >= 0 && x <= grid.width - 1) && (y >= 0 && y <= grid.height - 1)) //Neighbour is out of the grid
						{
							if (grid.grid[x][y].value == -1 || grid.grid[x][y].value == -4) // If the Cell is empty or its the end cell
							{
								foundempty = true; //found empty cell

								grid.grid[x][y].value = counter + 1; //Cells distance is previous distance + 1

								if (x == grid.end.x && y == grid.end.y) //If this cell is the end
								{
									foundend = true; //found end
								}
							}
						}
					}	
				
				}
			}
		}
		counter++; //increment counter
	}

	
	if (foundend) //If End is not found
	{
		 return true; //Peth Found
	}
	else
	{
		return false; //No Path Found
	}
}

//Lee Algorithm
bool Lee::findPath(Grid& grid)
{
	bool foundend=false;
	foundend = distGrid(grid); //Fill grid with distances and check if a path is available
	
	if (foundend) //If there is a path available
	{
		//Initialize Variables
		Coords currentPos;
		Coords smallest;
		bool foundStart = false;

		smallest = grid.end; //Smallest is the end
		currentPos = grid.end; //Current Cell is the end

		path.push_front(currentPos); //Push The end to the path

		while (!foundStart) //Loop until start is not found
		{
			for (int k = 0; k < 4; k++) //Loop for all neighbours
			{
				int x = currentPos.x + neighboursX[k]; // X coord of neighbour
				int y = currentPos.y + neighboursY[k]; //Y coord of neighbour

				//If Cell is not on the edge and the distance is smaller value than the current one
				if ((x >= 0 && x <= grid.width - 1) && (y >= 0 && y <= grid.height - 1) && (grid.grid[x][y].value < grid.grid[smallest.x][smallest.y].value) && (grid.grid[x][y].value >= 0))
				{
					smallest = { x, y }; //Smallest becomes current cell
				}

			}

			currentPos = smallest; //current position is the smallest distance neighbour

			if ((currentPos.x == grid.start.x) && (currentPos.y == grid.start.y)) //if the current position is the start
			{
				foundStart = true; // found start
				grid.grid[grid.start.x][grid.start.y].value = -3; //Set the start back to -3 for display purposes
			}
			else
			{
				path.push_front(smallest); //Push it to the path
			}
		}

		while (!path.empty()) //Loop until path is empty
		{
			grid.grid[path.front().x][path.front().y].value = 0; //Change the cells value to 0 for display purposes
			path.pop_front(); //pop front cell
		}
	}
	return foundend; //found end
}