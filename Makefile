CC=g++
CXXFLAGS=-Wall -Wextra -pedantic -std=c++14
FILES = menu.cpp Maze.cpp Generator.cpp DFSSolver.cpp
HEADERS = menu.h Maze.h Edge.h Cell.h Generator.h solver.h DFSSolver.h
DEBUG = -g
README = readme.txt

all:
	$(CC) $(CXXFLAGS) $(FILES) -o maze

debug:
	$(CC) $(CXXFLAGS) $(FILES) $(DEBUG) -o maze
	
archive:
	zip $(USER)-a1 $(FILES) $(HEADERS) $(README) $(MAKEFILE)