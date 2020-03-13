#ifndef DEF_MOUSE
#define DEF_MOUSE

#include <iostream>

#include "maze.h"

struct Tile
{
	int f_cost;
	int dist;
	int t_cost;
	int x;
	int y;
	bool empty;
};

class Mouse
{
	private:
		int m_x;
		int m_y;

		Maze m_mazeInt;
		Tile openList[MAZE_WIDTH*MAZE_WIDTH];
		Tile closedList[MAZE_WIDTH*MAZE_WIDTH];

		Tile vide;

	public:
		Mouse()
		{
			m_x=0;
			m_y=0;

			vide.empty=true;
			vide.x=-1;
			vide.y=-1;
			vide.dist=-1;
			vide.f_cost=-1;
			vide.t_cost=-1;

			for(int i=0; i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				openList[i]=vide;
				closedList[i]=vide;
			}
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

		void moveUp()
		{
			if(m_mazeInt.getWallUp(m_x,m_y)==0)
				m_x++;
		}
		void moveDown()
		{
			if(m_mazeInt.getWallDown(m_x,m_y)==0)
				m_x--;
		}
		void moveRight()
		{
			if(m_mazeInt.getWallRight(m_x,m_y)==0)
				m_y++;
		}
		void moveLeft()
		{
			if(m_mazeInt.getWallLeft(m_x,m_y)==0)
				m_y--;
		}

		Tile getOpenLowestCost()
		{
			//update costs
			for(int i=0; i<MAZE_WIDTH*MAZE_WIDTH; i++)
				updateCost(openList+i);

			// search for lowest cost tile // add distance from itself
			int i_min=0;
			int cost_min=openList[0].t_cost;
			int dist=openList[0].dist;
			for(int i=1; i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(!openList[i].empty)
				{
					if((openList[i].t_cost<cost_min)
							|| (openList[i].t_cost==cost_min && openList[i].dist<dist))
					{
						i_min=i;
						cost_min=openList[i].t_cost;
						dist=openList[i].dist;
					}
				}
			}
			Tile tile;
			tile=openList[i_min];

			// remove
			removeOpen(i_min);

			// add current to closed
			int n;
			for(n=0; !closedList[n].empty && n<MAZE_WIDTH*MAZE_WIDTH-1; n++){} // attention n<
			closedList[n]=tile;

			return tile;
		}

		void goTo(Tile tile)
		{
			//suitCouloir
			//faitDemiTour
			//intersection
		}

		void lookForNeighbour(Tile* neighbour)
		{
			for(int i=0; i<4; i++)
				neighbour[i]=vide;

			int index=0;
			if(!m_mazeInt.getWallUp(m_x,m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x+1;
				neighbour[index].y=m_y;
				setFCost(neighbour+index);
				updateCost(neighbour+index);
				index++;
			}
			if(!m_mazeInt.getWallDown(m_x,m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x-1;
				neighbour[index].y=m_y;
				setFCost(neighbour+index);
				updateCost(neighbour+index);
				index++;
			}
			if(!m_mazeInt.getWallRight(m_x,m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x;
				neighbour[index].y=m_y+1;
				setFCost(neighbour+index);
				updateCost(neighbour+index);
				index++;
			}
			if(!m_mazeInt.getWallLeft(m_x,m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x;
				neighbour[index].y=m_y-1;
				setFCost(neighbour+index);
				updateCost(neighbour+index);
				index++;
			}
		}

		bool isDestination(Tile tile)
		{
			return false;
		}


		void setFCost(Tile* tile)
		{
			if(!tile->empty)
			{
				// from start
				int g_cost=0;

				// to end
				int h_cost=0;

				// f_cost compute
				int f_cost=g_cost+h_cost;

				tile->f_cost=f_cost;
			}
		}

		void updateCost(Tile* tile)
		{
			if(!tile->empty)
			{
				tile->dist=1; // 

				tile->t_cost = tile->f_cost + tile->dist;
			}
		}

		void setPath(Tile* tile)
		{
		}

		bool isPathShorter(Tile current, Tile neighbour)
		{
			return false;
		}

		bool isInOpen(Tile tile)
		{
			return false;
		}

		void addInOpen(Tile tile)
		{
		}

		void removeOpen(int i)
		{
			openList[i]=vide;
			Tile back[MAZE_WIDTH*MAZE_WIDTH];
			int index_back=0;
			for(int i=0; i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(!openList[i].empty)
				{
					back[index_back]=openList[i];
					index_back++;
					openList[i]=vide;
				}
			}

			for(int i=0; i<index_back; i++)
			{
				openList[i]=back[i];
			}
		}

		void debug_showOpen()
		{
			cout << endl << "OpenList :" << endl;
			for(int i=0; i<5; i++)
			{
				cout << "- (" << openList[i].x << "," << openList[i].y << ") empty=" << openList[i].empty << " f_cost=" <<  openList[i].f_cost << " dist=" <<  openList[i].dist << " t_cost=" <<  openList[i].t_cost <<  endl;
			}
		}

		void debug_showTile(Tile tile)
		{

			cout << endl <<  "Tile=(" << tile.x << "," << tile.y << ") empty=" << tile.empty << " f_cost=" << tile.f_cost << " dist=" << tile.dist << " t_cost=" << tile.t_cost << endl;
		}

		void debug_showNeighbour(Tile* tiles)
		{
			for(int i=0; i<4; i++)
				cout << endl <<  "N["<<i<<"]=(" << tiles[i].x << "," << tiles[i].y << ") empty=" << tiles[i].empty << " f_cost=" << tiles[i].f_cost << " dist=" << tiles[i].dist << " t_cost=" << tiles[i].t_cost;

		}

		void explore(Maze* mazeExt)
		{
			// start tile
			Tile start;
			start.empty=false;
			start.x=m_x;
			start.y=m_y;
			start.f_cost=0;
			start.dist=0;
			start.t_cost=0;

			// add start node
			openList[0]=start;

			// variables
			Tile current;
			Tile neighbour[4];
			for(int i=0; i<4; i++)
				neighbour[i]=vide;

			// main loop to explore
			string choix;
			while(1)
			{
				cout << endl << endl << "avant" << endl;
				debug_showOpen();
				current=getOpenLowestCost();
				debug_showTile(current);
				debug_showOpen();

				//goTo(current);
				cin >> choix;
				if(choix=="z")
					moveUp();
				else if(choix=="d")
					moveRight();
				else if(choix=="s")
					moveDown();
				else if(choix=="q")
					moveLeft();
				checkWalls(mazeExt);
				showMap();

				if(isDestination(current))
					break;

				lookForNeighbour(neighbour); // return neighbour traversable and not in CLOSED

				debug_showNeighbour(neighbour);

				for(int i=0; !neighbour[i].empty && i<8; i++)
				{
					if(isPathShorter(current, neighbour[i]))
					{
						setFCost(neighbour+i);
						setPath(neighbour+i);
					}
					else if(!isInOpen(neighbour[i]))
					{
						setFCost(neighbour+i);
						setPath(neighbour+i);
						addInOpen(neighbour[i]);
					}
				}
			}
		}

		/*
		   A* algorithm
		   OPEN
		   CLOSED
		   add te start node to OPEN

		   loop
		   current = node in OPEN with the lowest f_cost
		   remoe current from OPEN
		   add current to CLOSED

		   if current is the target node
		   return
		   foreach neighbour of the current node
		   if neighbour is not traversable or nieghbour is in CLOSED
		   skip to the next neighbour

		   if new path to neighbour is shorter OR neighbour is not in OPEN
		   set f_cost of neighbour
		   set parent of neighbour to current
		   if neighbour is not in OPEN
		   add neighbour to OPEN
		 */
};

#endif
