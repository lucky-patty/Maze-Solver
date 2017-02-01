#include "menu.h"
using namespace std;

int readArguments(int argc, char*argv[])
{
    char* endPtr;
    array<unsigned,5> generatedSeed;
    Maze maze;
    
    regex mazeFile ("(.*)(.maze)(.*)");
    regex svgFile ("(.*)(.svg)(.*)");
    //if there are too many arguments, exit
        if(argc > MAX_ARG)
        return EXIT_FAILURE;
	
    //if user inputs --lb with a correct maze file name, calls the load binary method
    if(strcmp(argv[1], "--lb")==0 && !isdigit(argv[2][0]))
    {
        cout<<"loading from " << argv[2] <<endl;
        maze.loadBinaryFile(argv[2]);
    }
	
    //if user inputs --g with a correct seed, width and height calls the generate method
    if(strcmp(argv[1], "--g")==0)
    {
        //if user provides seed, widht and height
        if((isdigit(argv[2][0]) && isdigit(argv[3][0]) && isdigit(argv[4][0])  ))
        {
            Generator generator(strtol(argv[2], &endPtr, 10));
            maze.setupData( (int)strtol(argv[3], &endPtr, 10), (int)strtol(argv[4], &endPtr, 10) );
            generator.EllerGenerate(&maze);
        }
        //if user provides only width and height
        else if((isdigit(argv[2][0]) &&isdigit(argv[3][0]) ))
        {
            maze.setupData( (int)strtol(argv[2], &endPtr, 10), (int)strtol(argv[3], &endPtr, 10)  );
            seed_seq seq{(int)strtol(argv[2], &endPtr, 10), (int)strtol(argv[3], &endPtr, 10) };
            //generating a seed
            seq.generate(generatedSeed.begin(), generatedSeed.end());
            cout<<"Seed generated : " << generatedSeed[0]<<endl;
            Generator generator(generatedSeed[0]);
            generator.EllerGenerate(&maze);
        }
        //if user provides only seed, make width and height 10 each
        else if(isdigit(argv[2][0]) )
        {
            Generator generator(strtol(argv[2], &endPtr, 10));
            maze.setupData(10,10 );
            generator.EllerGenerate(&maze);
        }
        //when there are no number following --g
        else
        {
            cout<<"Not enough information for generating maze" <<endl;
            return EXIT_FAILURE;
        }
    }
	
	
    //checks all arguments whether user calls either --sb or --sv
    for(int i=0; i<argc-1; i++)
    {
        cout << "i : "<<i <<endl;
        cout<<"arg["<<i<<"] : " << argv[i]<<endl;
        if(strcmp(argv[i], "--sb") || strcmp(argv[i], "--sv"))
            //when there is no following argument of either --sb or --sv 
            if(i+1 >= argc)
            {
                return EXIT_FAILURE;
            }
        if(strcmp(argv[i], "--sb")==0)
            if(regex_match(argv[i+1], mazeFile))
                maze.saveBinaryFile(argv[i+1]);
        if(strcmp(argv[i], "--sv")==0)
            if(!isdigit(argv[i+1][0]))
                maze.saveSVGFile(argv[i+1]);	
    }
	
	
    return 1;
}



int main(int argc, char* argv[])
{	
	//readArguments(argc, argv);
	Maze maze;
	maze.loadBinaryFile(argv[1]);
	DFSSolver solver(&maze);
	solver.solve(&maze);
  
	
    return EXIT_SUCCESS;
	
}