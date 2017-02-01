#include "Generator.h"


using namespace std;

//constructor that takes seed value as parameter
Generator::Generator(long seedValue)
{
    seed = seedValue;
}

void Generator::setNSEW(int xA, int xB, int yA, int yB, Maze* maze)
{
    if(xA<xB && yA == yB)
    {
        maze -> cells[xA][yA].east = &(maze -> cells[xB][yB]);
        maze -> cells[xB][yB].west = &(maze -> cells[xA][yA]);
    }
    if(xA>xB && yA == yB)
    {
        maze -> cells[xA][yA].west =  &(maze -> cells[xB][yB]);
        maze -> cells[xB][yB].east = &(maze -> cells[xA][yA]);
    }
    if(xA==xB && yA < yB)
    {
        maze -> cells[xA][yA].north =  &(maze -> cells[xB][yB]);
        maze -> cells[xB][yB].south = &(maze -> cells[xA][yA]);
    }
    if(xA==xB && yA > yB)
    {
        maze -> cells[xA][yA].south = &(maze -> cells[xB][yB]);
        maze -> cells[xB][yB].north = &(maze -> cells[xA][yA]);
    }
}

//method to generate maze
void Generator::ABgenerate(Maze *maze)
{
    Cell* tempCell;
    Cell* loopCell;
    int edgesCreated = 0;
    int expectedEdges = (*maze).getWidth() * (*maze).getHeight() - 1;
    int width = (*maze).getWidth();
    int height = (*maze).getHeight();
    unsigned int a,b, randomNeighbour = MAX_NEIGHBOUR;
    //new mt19937 object created with existing seed
    mt19937 random(seed);
    //creating objects of uniform_int_distribution to limit the minimum and maximum value
    uniform_int_distribution<int> initWidthLimit(0, width-1);
    uniform_int_distribution<int> initHeightLimit(0, height-1);
    //generating a pseudo random number as initial coordinate, and save the cell of that coordinate to tempCell
    a = initWidthLimit(random);
    b = initHeightLimit(random);
    tempCell = &(maze -> cells[a][b]);
    tempCell->visited = true;
    uniform_int_distribution<int> neighbourCell(0, MAX_NEIGHBOUR - 1);
    //it will do the loop until the expected edges value is met
    while(edgesCreated <expectedEdges)
    {
        //nested loop to retrieve a random neighbour
        do
        {
            randomNeighbour = neighbourCell(random);
        }
        while(randomNeighbour > (tempCell->neighbours.size()-1 ));
		
        //getting the neighbour
        loopCell = tempCell->neighbours[randomNeighbour];
        //if it hasn't been visited yet, mark visited and create an edge of it and the current cell
        if(loopCell->visited == false)
        {
            loopCell->visited = true;
            Edge edge;
            edge.xCellA = tempCell->x;
            edge.yCellA = tempCell->y;
            edge.xCellB = loopCell->x;
            edge.yCellB = loopCell->y;
            setNSEW(edge.xCellA, edge.xCellB, edge.yCellA, edge.yCellB, maze);
		    setNSEW(1,1,0,1,maze);
            edgesCreated++;
            (maze -> edges).push_back(edge);
        }
        //change the current cell (tempCell) to the new cell
        tempCell = loopCell;		
	}
	
}

void Generator::EllerGenerate(Maze*maze)
{
    uniform_int_distribution<int> boolean(0, 1);
    mt19937 random(seed);
    int width = (*maze).getWidth();
    int height = (*maze).getHeight();
    int connected = 0, vertical = 0, currentHt = 0; //indicators for various conditions
	int i, j, x,currentWidth; //loop counters
	int tempSetNumber1 = 0, tempSetNumber2 = 0;
	int setNumberCounter = 1;
	vector<vector<int>> setNumbers;	
	vector<int> verticalCheckSet;
	vector<vector<bool>> visited;
	vector<vector<Cell*>>sets;
	vector<int>::iterator it;
	vector<bool>::iterator itBool;
	vector<bool> minimumVertical;
	
	for(i = 0; i < height ; i++)
	{
		vector<int> set;
		for(j = 0; j < width; j++)
		{
			set.push_back(0);
		}
		setNumbers.push_back(set);
	}
	
	for(i = 0; i < height; i++)
	{
		vector<bool> visitedRow;
		for(j=0; j<width; j++)
		{
			visitedRow.push_back(false);
		}
		visited.push_back(visitedRow);
	}
	
	for(currentHt = 0 ; currentHt < height ; currentHt++)
	{
		for(currentWidth = 0; currentWidth < width; currentWidth++)
		{
			connected = boolean(random);
			if(currentHt == height-1)
				connected = 1;
			cout<<"HEIGHT : " << currentHt << " WIDTH : " << currentWidth << " CONNECTED : " <<connected<<endl;
			if(currentWidth == 0)
			{
				if(!visited[currentHt][currentWidth])
				{
					setNumbers[currentHt][currentWidth] = setNumberCounter;
					setNumberCounter++;
					visited[currentHt][currentWidth] = true;
				}
				continue;
			}
			if(setNumbers[currentHt][currentWidth] == setNumbers[currentHt][currentWidth-1])
				continue;
			if(connected == 1 && visited[currentHt][currentWidth-1] && !visited[currentHt][currentWidth])
			{
				Edge e;
				e.xCellA = currentWidth;
				e.yCellA = currentHt;
				e.xCellB = currentWidth - 1;
				e.yCellB = currentHt;
				(maze -> edges).push_back(e);
				
				visited[currentHt][currentWidth] = true;
				setNumbers[currentHt][currentWidth] = setNumbers[currentHt][currentWidth-1];
				
			}
			else if(connected == 1 && visited[currentHt][currentWidth-1] && visited[currentHt][currentWidth]
						&& setNumbers[currentHt][currentWidth-1] == setNumbers[currentHt][currentWidth])
			{
				Edge e;
				e.xCellA = currentWidth;
				e.yCellA = currentHt;
				e.xCellB = currentWidth - 1;
				e.yCellB = currentHt;
				(maze -> edges).push_back(e);
			}

			else if(connected == 1 && visited[currentHt][currentWidth-1] && visited[currentHt][currentWidth])
			{
				Edge e;
				e.xCellA = currentWidth;
				e.yCellA = currentHt;
				e.xCellB = currentWidth - 1;
				e.yCellB = currentHt;
				(maze -> edges).push_back(e);
				
				tempSetNumber1 = setNumbers[currentHt][currentWidth-1];
				tempSetNumber2 = setNumbers[currentHt][currentWidth];
				
				for(i = 0; i < height ; i++)
				{
					for(j = 0; j < width; j++)
					{
						if(setNumbers[i][j] == tempSetNumber1
							|| setNumbers[i][j] == tempSetNumber2)
							setNumbers[i][j] = setNumberCounter;
					}
				}
				setNumberCounter++;
			}
			
			else if(connected == 0 && !visited[currentHt][currentWidth])
			{
				visited[currentHt][currentWidth]  = true;
				setNumbers[currentHt][currentWidth] = setNumberCounter;
				setNumberCounter++;
			}
			
			else if(connected == 0 && visited[currentHt][currentWidth] )
				continue;
		}
		
		
		for(i = 0; i < width; i++)
		{
			it = find(verticalCheckSet.begin(), verticalCheckSet.end(), setNumbers[currentHt][i]);
			if( it == verticalCheckSet.end())	
				verticalCheckSet.push_back(setNumbers[currentHt][i]);
		}
		
		for(i = 0; i < width; i++)
		{
			minimumVertical.push_back(false);
		}
		
		if(currentHt == height-1)
			break;
		
		do
		{
			for(i = 0; i < width; i++)
			{
				if(!minimumVertical[i])
				{
					connected = boolean(random);
					if(connected == 1)
					{
						Edge e;
						e.xCellA = i;
						e.yCellA = currentHt;
						e.xCellB = i;
						e.yCellB = currentHt + 1;
						(maze -> edges).push_back(e);
						setNumbers[currentHt + 1][i] = setNumbers[currentHt][i];
						//verticalCheckSet.erase(remove_if(verticalCheckSet.begin(), verticalCheckSet.end, setNumbers[currentHt][i]),
							//verticalCheckSet.end())
						minimumVertical[i] = true;
						visited[currentHt+1][i] = true;
					}
				}
			}
			
			for(i = 0; i < width; i++)
			{
				if(!minimumVertical[i])
				{
					x = setNumbers[currentHt][i];
					for(j = 0; j < width; j++)
					{
						if(setNumbers[currentHt][j] == x && minimumVertical[j] )
						{
							minimumVertical[i] = true;
							break;
						}
					}
				}
			}
			
			vertical = 1;
			for(i = 0; i < width; i++)
			{
				if(!minimumVertical[i])
					vertical = 0;
			}
		}
		while(vertical == 0);
		
		verticalCheckSet.clear();
		minimumVertical.clear();
		
		
	}
	
	/*for(currentWidth = 0; currentWidth < width-1; currentWidth++)
	{
		if(currentWidth == 0)
		{
			if(!visited[currentHt][currentWidth])
			{
				setNumbers[currentHt][currentWidth] = setNumberCounter;
				setNumberCounter++;
				visited[currentHt][currentWidth] = true;
			}
			continue;
		}
		if(setNumbers[currentHt][])
	}*/
	
	/*for(currentWidth = 0; currentWidth < width-1; currentWidth++)
	{
		Edge e;
		e.xCellA = currentWidth;
		e.yCellA = currentHt;
		e.xCellB = currentWidth +1;
		e.yCellB = currentHt;
		(maze -> edges).push_back(e);
		
	}*/
	cout<<"SET NUMBERS" << endl;
	for(i = 0; i < height ; i++)
	{
		for(j = 0; j < width; j++)
		{
			cout << setNumbers[i][j] << " ";
		}
		cout<<endl;
	}
	
	
	
}

 


int Generator::checkVertical(vector<Cell*> set, int row)
{
    for(Cell* cell: set)
    {
        if(cell->south && cell->y == row)
            return 1;
    }
	return 0;
}

int Generator::findSetNumber(vector<vector<Cell*>> sets, int x, int y)
{
	for(vector<Cell*>::size_type j = 0; j < sets.size(); j++)
	{
		for(Cell* cell : sets[j])
		{
			if ( cell->x == x && cell->y == y)
				return j;
		}
	}
	return -1;
}











