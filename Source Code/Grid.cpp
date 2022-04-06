#include "Grid.h"
#include <iostream>

Grid::Grid()
{
	srand(time(NULL));
}

//Update the grid 
void Grid::updateGrid(int noRows, int noColumns)
{
	grid.clear(); //clear the current grid

	std::vector<Cells> rows;

	for (int i = 0; i < noColumns; i++)//Loop for all columns
	{
		rows.clear();//clear all previous rows
		for (int j = 0; j < noRows; j++)//Loop for all rows
		{
			//Initialize new Cell
			Cells newCell;
			newCell.coords = {i,j};
			newCell.value = -1;
			rows.push_back(newCell); //Push Back Cell into rows
		}
		grid.push_back(rows); //Push Back Row into grid
	}
}

//Reset Grid
void Grid::resetGrid()
{
	updateGrid(height, width); //Update Grid With Same Height and Width
	start = { -1,-1 }; //Reset Start
	end = { -1,-1 }; //Reset End
}

//Fill Grid With Random Walls
void Grid::randomWalls()
{
	for (int j = 0; j < height; j++) //Loop through all rows
	{
		for (int i = 0; i < width; i++) //Loop through all columns
		{
			int randNum = rand() % 5; //Get s random number from 0-5

			if (randNum == 1 && grid[i][j].value ==-1) //If random number is 1 and current cell is nothing
			{
				grid[i][j].value = -2; //Set Cell to Wall
			}
		}
	}
}