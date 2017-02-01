#include "BFSSolver.h"
#define START_POINT 0
#define CAN_SOLVE 1
#define CANT_SOLVE -1

using namespace std;

/*
	List of testing 

	- Verify the data from the maze *m 
	- Print visited 
	- Draw the maze 

*/
int BFSSolver::solve(Maze *m)
{
	// Variables
	vector<vector<Cell>> visited = m.cells; // Check Visited Cell
	Edge e = new Edge(); // Edge for push back into the path
	queue<Cell*> cells_queue; // Expansion area 
	Cell * current_cell = nullptr; // Current Cell
	Cell * first_cell , last_cell , neighbour_cell;

	// Initializes Cell
	visited[START_POINT][START_POINT].visited = true;
	current_cell = visited[START_POINT][START_POINT];  
	last_cell.x = xFinish;
	last_cell.y = yFinish;

	// Mark the current node as visited and enqueue it 
	cells_queue.push(current_cell);

	// While we have cells 
	while(!cells_queue.empty())
	{

		// Grab the First
		current_cell = cells_queue.front();
		cells_queue.pop();

		// Reach the last cell = Problem Solved !
		if(current_cell.x == last_cell.x && current_cell.y == last_cell.y)
		{
			// Print The PathSaver 
			drawPath(path, "testBFSpath1.svg", yFinish+1); // Path is vector<Edges>
			return CAN_SOLVE;
		}
		else
		{
			// Find Unvisited Neighbour
			for(auto i = current_cell.neighbours.begin(); i!=current_cell.neighbours.end(); i++)
			{
				neighbour_cell = current_cell.neighbours.at(i);
				cout << "------------------------------------------" << endl;
				cout << "Nighbours Cell X : " << neighbour_cell.x << endl;
				cout << "Nighbours Cell Y : " << neighbour_cell.y << endl;
				cout << "Nighbours Cell Visited : " << neighbour_cell.visited << endl;
				cout << "------------------------------------------" << endl;
				
				// If it not visited -> mark it and add to queue

				if(neighbour_cell.visited == false)
				{
					// Set A point 
					e.xCellA = current_cell.x;
					e.yCellA = current_cell.y;
					// Set B Point
					e.xCellB = neighbour_cell.x;
					e.yCellB = neighbour_cell.y;

					neighbour_cell.visited = true ; // Mark it as visited 
					current_cell.neighbours.at(i).visited = true; // Test Purpose

					cells_queue.push(neighbour_cell);
					path.push_back(e);
					e = new Edge(); // Initialize to empty again
				}
				 
			}
		}

	}

	return CANT_SOLVE;
}