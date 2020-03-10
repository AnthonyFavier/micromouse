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

	Mouse mouse;
	mouse.checkWalls(&maze);
	mouse.showMap();

	string choix;
	while(1)
	{
		cin >> choix;

		if(choix=="z")
			mouse.moveUp();
		else if(choix=="d")
			mouse.moveRight();
		else if(choix=="s")
			mouse.moveDown();
		else if(choix=="q")
			mouse.moveLeft();
		mouse.checkWalls(&maze);
		mouse.showMap();
	}

	return 0;
}

