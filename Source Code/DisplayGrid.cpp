#include "DisplayGrid.h"

DisplayGrid::DisplayGrid()
{
	//Initialize Grid Rectangle
	gridGuidelinesSize.x = 2000;
	gridGuidelinesSize.y = 1200;
	gridGuidelines.setSize(sf::Vector2f(gridGuidelinesSize.x, gridGuidelinesSize.y));
	gridGuidelines.setPosition(0, 400);
	gridGuidelines.setOutlineColor(sf::Color::Black);
	gridGuidelines.setOutlineThickness(5);
	gridGuidelines.setFillColor(sf::Color::White);

	//Initialize Start and End Rectangles
	startRect.setFillColor(sf::Color::Green);
	startRect.setPosition(-10000,0);
	endRect.setFillColor(sf::Color::Red);
	endRect.setPosition(-10000, 0);

}

//Change the grid width or height
void DisplayGrid::setGridPositions(int rows, int columns,Grid &grid)
{
	//The size of the box holding the grid
	gridGuidelinesSize.x -= gridGuidelinesSize.x % columns;
	gridGuidelinesSize.y -= gridGuidelinesSize.y % rows;
	gridGuidelines.setSize(sf::Vector2f(gridGuidelinesSize.x, gridGuidelinesSize.y));

	//The distance between lines
	diff.x = (gridGuidelinesSize.x/columns);
	diff.y = (gridGuidelinesSize.y / rows);
	
	//Distance between edge of window and grid line box.
	spaceLeft.x = 2000 - gridGuidelinesSize.x;
	spaceLeft.x /= 2;
	spaceLeft.y = 1900 - gridGuidelinesSize.y;
	spaceLeft.y /= 2;
	gridGuidelines.setPosition(spaceLeft.x,spaceLeft.y);
	
	gridLines.clear();	//Clear the lines the we already have


	Coords current = diff;

	//Loop for all rows
	for (int i = 0; i < (rows-1); i++)
	{
		//Initialize line object
		sf::RectangleShape line(sf::Vector2f(gridGuidelinesSize.x,1));
		line.setPosition(spaceLeft.x,current.y+spaceLeft.y);
		line.setFillColor(sf::Color::Black);

		gridLines.push_front(line); //Add line to list
		current.y += diff.y; //Increment current.y
	}

	//Loop for all columns
	for (int j = 0; j < (columns-1); j++)
	{
		//Initialize line object
		sf::RectangleShape line(sf::Vector2f(1, gridGuidelinesSize.y));
		line.setPosition(current.x+spaceLeft.x, spaceLeft.y);
		line.setFillColor(sf::Color::Black);

		gridLines.push_front(line); //Add line to list
		current.x += diff.x; //Increment current.x
	}
	
	//Update Width and Height 
	grid.width = columns;
	grid.height = rows;	

	//Set Size of the Start and End Rectangle
	startRect.setSize(sf::Vector2f(diff.x, diff.y));
	endRect.setSize(sf::Vector2f(diff.x, diff.y));

	//Reset Display and Grid
	resetDislpay();
	grid.resetGrid();

	//Reset Grid Guidlines
	gridGuidelinesSize.x = 2000;
	gridGuidelinesSize.y = 1200;
}

//Render
void DisplayGrid::render(sf::RenderWindow* window)
{
	window->draw(gridGuidelines); //GuidlinesBox

	for (auto p : pathRects) //Loop for all pathRects
	{
		window->draw(p); //render path Rect
	}

	for (auto w : wallRects) //Loop for all wallRects
	{
		window->draw(w); //render wall Rect
	}

	window->draw(startRect); //Start Rect
	window->draw(endRect); //End Rect

	for (auto l : gridLines) //Loop for all gridLines
	{
		window->draw(l); //render grid line
	}
}

//Reset Display 
void DisplayGrid::resetDislpay()
{
	startRect.setPosition(-10000, 0);
	endRect.setPosition(-10000, 0);
	wallRects.clear();
	pathRects.clear();
}

//Check Collisions Grid and mouse
void DisplayGrid::collisionCheck(Coords mouse, Grid& grid,int drawingMode)
{
	//Check if collision is on grid
	if (Collisions::pointToAABB({ gridGuidelines.getPosition().x + gridGuidelines.getSize().x,gridGuidelines.getPosition().y + gridGuidelines.getSize().y }, { gridGuidelines.getPosition().x,gridGuidelines.getPosition().y }, mouse))
	{
		for (auto j : grid.grid) //Loop for all cells
		{
			for (auto i : j)
			{
				//Check if collision is on current cell
				if (Collisions::pointToAABB({ (float)((i.coords.x * diff.x) + diff.x + spaceLeft.x),(float)((i.coords.y * diff.y) + spaceLeft.y + diff.y) }, { (float)((i.coords.x * diff.x) + spaceLeft.x),(float)((i.coords.y * diff.y) + spaceLeft.y )}, mouse))
				{
	
					if (drawingMode == 1)//Draw Start
					{
						if (grid.start.x >= 0) //If start is already on board
						{
							grid.grid[grid.start.x][grid.start.y].value = -1; //make that cell into nothing
						}
						grid.grid[i.coords.x][i.coords.y].value = -3; //make the new cell into start
					}
					else
					{
						if (drawingMode == 2)//Draw End
						{
							if (grid.end.x >= 0) //If end  is already on board
							{
								grid.grid[grid.end.x][grid.end.y].value = -1; //make that cell into nothing
							}
							grid.grid[i.coords.x][i.coords.y].value = -4; //make the new cell into end
						}
						else
						{
							//Draw Walls
							if ((i.coords.x != grid.start.x || i.coords.y != grid.start.y) && (i.coords.x != grid.end.x || i.coords.y != grid.end.y)) //If this cell is not the end or start
							{
								if (i.value == -1) //If its empty
								{
									grid.grid[i.coords.x][i.coords.y].value = -2; //Make that cell into a wall
								}
							}
						}
					}
				}
			}
		}
	}
	displayEverything(grid);
}

void DisplayGrid::displayEverything(Grid& grid)
{
	resetDislpay();
	for (auto j : grid.grid)
	{
		for (auto i : j)
		{
			switch (i.value)
			{

			case -2:
			{
				sf::RectangleShape wall;
				wall.setFillColor(sf::Color::Cyan);
				wall.setSize(sf::Vector2f(diff.x, diff.y));
				wall.setPosition(i.coords.x * diff.x + spaceLeft.x, i.coords.y * diff.y + spaceLeft.y);
				wallRects.push_front(wall);
			}
			break;

			case -3:
			{
				grid.start = i.coords;
				startRect.setPosition(grid.start.x * diff.x + spaceLeft.x, grid.start.y * diff.y + spaceLeft.y);
			}
				break;

			case -4:
			{
				grid.end = i.coords;
				endRect.setPosition(grid.end.x * diff.x + spaceLeft.x, grid.end.y * diff.y + spaceLeft.y);
			}
				break;

			case 0:
			{
				sf::RectangleShape path;
				path.setFillColor(sf::Color::Yellow);
				path.setSize(sf::Vector2f(diff.x, diff.y));
				path.setPosition(i.coords.x * diff.x + spaceLeft.x , i.coords.y * diff.y + spaceLeft.y);
				pathRects.push_front(path);
			}
				break;

			default:
				break;
			}
		}
	}
}