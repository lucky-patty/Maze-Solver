#ifndef DjikstaSolver_H
#define DjikstraSolver_H

#include "solver.h"
#include "Maze.h"

class DjikstraSolver : public Solver{
protected:

public:
	int solve (Maze * );
	void euclideanApply (Maze *);
	void manhattanApply (Maze *);
}