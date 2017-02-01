#ifndef CELL_H
#define CELL_H

#include "Edge.h"
#include<vector>
#define MAX_NEIGHBOUR 4

//struct for cell, contains coordinate, visited value (for generating maze) and references to its neighbours (max 4 neighbours)
typedef struct Cell {
    int x;
    int y;
    bool visited = false;
    double value = 0; // Euclidean & Manhatten
    std::vector<Cell*> neighbours;

    Cell* north=NULL;
    Cell* south=NULL;
    Cell* east=NULL;
    Cell* west=NULL;
}Cell;

#endif