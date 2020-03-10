#ifndef DEF_MOUSE
#define DEF_MOUSE

#include <iostream>

#include "maze.h"

class Mouse
{
	private:
		int m_x;
		int m_y;

		Maze m_mazeInt;

	public:
		Mouse()
		{
			m_x=0;
			m_y=0;
		}

		int getX(){return m_x;}
		int getY(){return m_y;}

		void checkWalls(Maze* mazeExt)
		{
			bool wallUp=false;
			bool wallDown=false;
			bool wallLeft=false;
			bool wallRight=false;

			wallUp=mazeExt->getWallUp(m_x,m_y);
			wallDown=mazeExt->getWallDown(m_x,m_y);
			wallLeft=mazeExt->getWallLeft(m_x,m_y);
			wallRight=mazeExt->getWallRight(m_x,m_y);

			m_mazeInt.setWallUp(m_x,m_y,wallUp);
			m_mazeInt.setWallDown(m_x,m_y,wallDown);
			m_mazeInt.setWallLeft(m_x,m_y,wallLeft);
			m_mazeInt.setWallRight(m_x,m_y,wallRight);	
		}

		void showMap()
		{
			m_mazeInt.show(m_x,m_y);
		}

		void moveUp(){m_x++;}
		void moveDown(){m_x--;}
		void moveLeft(){m_y--;}
		void moveRight(){m_y++;}
};

#endif
