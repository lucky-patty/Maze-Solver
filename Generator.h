#ifndef Generator_H
#define Generator_H

#include<stdlib.h>
#include<random>
#include<vector>
#include<algorithm>

#include "Maze.h"
#include "Edge.h"
class Generator
{
    private:
    long seed;
	

    public:
    Generator(long);
    void setNSEW(int,int,int,int, Maze*);
    void ABgenerate(Maze*);
	void EllerGenerate (Maze*);
	int checkVertical(std::vector<Cell*>, int); 
	int findSetNumber(std::vector<std::vector<Cell*>>, int, int);
};

#endif