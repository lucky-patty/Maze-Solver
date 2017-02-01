#ifndef BFSSolver_H
#define BFSSolver_H

#include "solver.h"
#include "Maze.h"
#include "Cell.h"

using namespace std;
class BFSSolver : public Solver{
protected:
	vector<vector<Cell>> visited;
public:
	int solve (Maze * );
	
}