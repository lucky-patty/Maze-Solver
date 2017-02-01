#ifndef Solver_H
#define Solver_H

#include "Maze.h"
#include "Edge.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
class Solver{
	protected:
		int xStart = 0;
		int yStart = 0;
		int xFinish;
		int yFinish;
		std::vector<Edge> path;
	
	public:
		bool findEdge(std::vector<Edge> edges, int xA, int yA, int xB, int yB)
		{
			for(Edge e : edges)
				if( e.xCellA == xA && e.xCellB == xB && e.yCellA ==yA && e.yCellB == yB)
					return true;
				else if (e.xCellA == xB && e.xCellB == xA && e.yCellA ==yB && e.yCellB == yA) 
					return true;
			return false;
		}

		virtual int solve(Maze *)=0;
		Solver(Maze * maze)
		{
			xFinish = maze->getWidth()-1;
			yFinish = maze->getHeight()-1;
		}
		
		void drawPath(std::vector<Edge> edges, char* fileName, int width)
		{
			//opening SVG files to write data into
			ofstream file(fileName);
			//writing width and height with SVG format
			file << "<svg width='"<< MAZE_SIZE <<"' height='"<< MAZE_SIZE <<"' xmlns='http://www.w3.org/2000/svg'>"<<endl;
			file << "<rect width='"<< MAZE_SIZE <<"' height ='"<< MAZE_SIZE <<"' style='fill:black'/>"<<endl;
			//iterates through each edge in the maze to print its datas
			for(Edge e: edges)
			{
				file <<"<line stroke='white' stroke-width='"<<(float)MAZE_SIZE/(width*2)<<"' ";
				file << "x1= '"<< (float)e.xCellA / width * MAZE_SIZE<<"' ";
				file << "y1= '"<< (float)e.yCellA / width * MAZE_SIZE<<"' ";
				file << "x2= '"<< (float)e.xCellB / width * MAZE_SIZE<<"' ";
				file << "y2= '"<< (float)e.yCellB / width * MAZE_SIZE<<"' ";
				file << "/>"<<endl;
			}
			file<<"</svg>";
		}
};

#endif