#include "DFSSolver.h"

using namespace std;

int DFSSolver::solve(Maze * maze)
{
	bool solved = false;
	int currentX = xStart, currentY = yStart;
	vector<vector<bool>> visited;
	vector<vector<int>> weights;
	bool left = false, right = false, up = false, down = false;
	int i, j;
	for(i = 0; i < yFinish+1; i++)
	{
		vector<bool> visitedRow;
		for(j=0; j<xFinish+1; j++)
		{
			visitedRow.push_back(false);
		}
		visited.push_back(visitedRow);
	}
	for( i = 0; i < yFinish+1 ; i++)
	{
		vector<int> weight;
		for( j = 0; j<xFinish+1; j++)
			weight.push_back(0);
		weights.push_back(weight);
	}
	cout<<"VISITED"<<endl;
	for(i = 0; i < yFinish+1; i++)
	{
		for(j=0; j<xFinish+1; j++)
		{
			cout<<visited[i][j]<<" ";
		}
		cout<<endl;
	}
		visited[0][0] = true;
	while(!visited[yFinish][xFinish])
	{
		left = false; right = false; up = false; down = false;
		right = findEdge(maze->edges, currentX, currentY, currentX+1, currentY);
		down = findEdge(maze->edges, currentX, currentY, currentX, currentY+1);
		left = findEdge(maze->edges, currentX, currentY, currentX-1, currentY);
		up = findEdge(maze->edges, currentX, currentY, currentX, currentY-1);
		cout<<"currentX : " <<currentX <<" currentY : " <<currentY<<endl;
		
		if(up && weights[currentY-1][currentX] == 0) 
		{
			//if(currentY-1 != 0 && currentX != 0)
				weights[currentY-1][currentX] = weights[currentY][currentX] + 1;
			
			/*Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX;
			e.yCellB = currentY - 1;
			path.push_back(e);*/
		}
		if(down && weights[currentY+1][currentX] == 0)
		{
			weights[currentY+1][currentX] = weights[currentY][currentX] + 1;
			
			/*Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX;
			e.yCellB = currentY + 1;
			path.push_back(e);*/
		}
		if(left && weights[currentY][currentX-1] == 0)
		{
			//if(currentX-1 != 0 && currentY != 0)
				weights[currentY][currentX-1] = weights[currentY][currentX] + 1;
			
			/*Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX - 1;
			e.yCellB = currentY;
			path.push_back(e);*/
		}
		if(right && weights[currentY][currentX+1] == 0)
		{
			weights[currentY][currentX+1] = weights[currentY][currentX] + 1;
			
			/*Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX + 1;
			e.yCellB = currentY;
			path.push_back(e);*/
		}
		if(currentX < xFinish)
			if(visited[currentY][currentX+1])
			{
				right = false;
			}
		if(currentX>0)
			if(visited[currentY][currentX-1])
			{
				left = false;
			}
		if(currentY > 0)
			if(visited[currentY-1][currentX])
			{
				up = false;
			}
		if(currentY<yFinish)
			if(visited[currentY+1][currentX])
			{
				down = false;
			}
		
		if(right)
		{
			Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX + 1;
			e.yCellB = currentY;
			path.push_back(e);
			cout<<"RIGHT"<<endl;
			visited[currentY][currentX+1] = true;
			currentX++;
			continue;
		}
		else if(down)
		{
			Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX;
			e.yCellB = currentY + 1;
			path.push_back(e);
			cout<<"DOWN"<<endl;
			visited[currentY+1][currentX] = true;
			currentY++;
			continue;
		}
		else if(left)
		{
			Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX - 1;
			e.yCellB = currentY;
			path.push_back(e);
			cout<<"LEFT"<<endl;
			visited[currentY][currentX-1] = true;
			currentX--;
			continue;
		}
		else if(up)
		{
			Edge e;
			e.xCellA = currentX;
			e.yCellA = currentY;
			e.xCellB = currentX;
			e.yCellB = currentY - 1;
			path.push_back(e);
			cout<<"UP"<<endl;
			visited[currentY-1][currentX] = true;
			currentY--;
			continue;
		}
		
		if((!up && !down && !right && !left) 
			|| (visited[currentY+1][currentX] && visited[currentY-1][currentX] && visited[currentY][currentX+1]
					&& visited[currentY][currentX-1]))
		{
			path.pop_back();
			if(path.empty())
			{
				currentX = 0;
				currentY=0;
			}
			else
			{
				currentX = path.back().xCellB;
				currentY = path.back().yCellB;
			}
			
			
		}
	}
	cout << "WEIGHTS"<<endl;
	for(int i = 0; i < yFinish+1 ; i++)
	{
		for(int j = 0; j<xFinish+1; j++)
			cout << weights[i][j] <<" ";
		cout<<endl;
	}
	drawPath(path, "testpath1.svg", yFinish+1);
	return 1;
}


bool DFSSolver::allAdjVisit(vector<vector<bool>> visited, int currentX, int currentY)
{
	if(currentX > 0 && currentY > 0 && currentY < yFinish && currentX < xFinish)
		if(visited[currentX-1][currentY] && visited[currentX][currentY-1] 
		&& visited[currentX+1][currentY] && visited[currentX][currentY+1])
			return true;
	else if(currentY > 0)
		cout<<"TEST";
	return false;
}













