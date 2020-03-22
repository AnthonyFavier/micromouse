#include <iostream>
#include <stdlib.h>

#include "maze.h"
#include "mouse.h"

using namespace std;

int main(int argc, char** argv)
{
	Maze maze;
	maze.draw();
	maze.show();

	if(argc==1)
	{
		Mouse mouse;
		mouse.checkWalls(&maze);

		while(1)// timer ok
			mouse.FSM(&maze);
		//stop mouse
	}

	return 0;
}

