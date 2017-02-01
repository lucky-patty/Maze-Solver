
#ifndef MAZE_H
#define MAZE_H
#include "Cell.h" // File
// Include Necessary Library
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<vector>
#define MAZE_SIZE 1000

//Class structure for Maze
class Maze {
        protected:
        int width;
        int height;
        int noEdges = 0;
        double value ;
		
    public:
        std::vector<Edge> edges;
        std::vector<std::vector<Cell>> cells;
        void loadBinaryFile(char[]);
        void saveBinaryFile(char*);
        void saveSVGFile(char* );
        void generateCells(void );
        void setNeighbours(void);
        void printEdges();
        int getWidth();
        int getHeight();
        void setupData(int, int);
        Maze(int,int);
        Maze();
		
};

#endif
