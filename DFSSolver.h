#ifndef DFSSolver_H
#define DFSSolver_H

#include "solver.h"
#include "Maze.h"

class DFSSolver: public Solver{
	protected:
	
	public:
		int solve(Maze *);
		DFSSolver(Maze * maze) : Solver::Solver (maze){};
		bool allAdjVisit(vector<vector<bool>> , int , int );
};

#endif