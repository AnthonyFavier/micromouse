#ifndef DEF_MOUSE
#define DEF_MOUSE

#include <iostream>

#include "maze.h"
#include "tile.h"


class Mouse
{
	private:
		int m_x;
		int m_y;

		int m_start_x;
		int m_start_y;

		int m_end_x;
		int m_end_y;

		Maze m_mazeInt;
		Tile m_openList[MAZE_WIDTH*MAZE_WIDTH];
		Tile m_closedList[MAZE_WIDTH*MAZE_WIDTH];

		Tile vide;

	public:
		Mouse()
		{
			m_start_x=0;
			m_start_y=0;

			m_x=m_start_x;
			m_y=m_start_y;

			vide.empty=true;
			vide.x=-1;
			vide.y=-1;
			vide.dist=0;
			vide.f_cost=-1;
			vide.t_cost=-1;
			vide.p_x=-1;
			vide.p_y=-1;

			m_end_x=-1;
			m_end_y=-1;

			for(int i=0; i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				m_openList[i]=vide;
				m_closedList[i]=vide;
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
			m_mazeInt.show(m_x,m_y,m_openList,m_closedList);
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
				updateCost(m_openList+i);

			// search for lowest cost tile // add distance from itself
			int i_min=0;
			int cost_min=m_openList[0].t_cost;
			int dist=m_openList[0].dist;
			for(int i=1; i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(!m_openList[i].empty)
				{
					if((m_openList[i].t_cost<cost_min)
							|| (m_openList[i].t_cost==cost_min && m_openList[i].dist<dist))
					{
						i_min=i;
						cost_min=m_openList[i].t_cost;
						dist=m_openList[i].dist;
					}
				}
			}
			Tile tile;
			tile=m_openList[i_min];

			// remove
			removeOpen(i_min);

			// add current to closed
			int n;
			for(n=0; !m_closedList[n].empty && n<MAZE_WIDTH*MAZE_WIDTH-1; n++){} // attention n<
			m_closedList[n]=tile;

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
			if(!m_mazeInt.getWallUp(m_x,m_y)
					&& !isInClosed(m_x+1, m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x+1;
				neighbour[index].y=m_y;
				index++;
			}
			if(!m_mazeInt.getWallDown(m_x,m_y)
					&& !isInClosed(m_x-1, m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x-1;
				neighbour[index].y=m_y;
				index++;
			}
			if(!m_mazeInt.getWallRight(m_x,m_y)
					&& !isInClosed(m_x, m_y+1))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x;
				neighbour[index].y=m_y+1;
				index++;
			}
			if(!m_mazeInt.getWallLeft(m_x,m_y)
					&& !isInClosed(m_x, m_y-1))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x;
				neighbour[index].y=m_y-1;
				index++;
			}
		}

		bool isDestination(Tile tile)
		{
			bool arrive=false;
			if((tile.x==MAZE_WIDTH/2-1 || tile.x==MAZE_WIDTH/2)
					&& (tile.y==MAZE_WIDTH/2-1 || tile.y==MAZE_WIDTH/2))
				arrive=true;
			return arrive;
		}

		void setFCost(Tile* tile)
		{
			if(!tile->empty)
			{
				// from start
				int g_cost=1;
				int cp_x=tile->p_x;
				int cp_y=tile->p_y;
				while(cp_x!=m_start_x || cp_y!=m_start_y)
				{
					for(int i=0; !m_closedList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
					{
						if(m_closedList[i].x==cp_x && m_closedList[i].y==cp_y)
						{
							cp_x=m_closedList[i].p_x;
							cp_y=m_closedList[i].p_y;
							g_cost++;
							break;
						}
					}
				}

				// to end
				int h_cost=0;
				if(tile->x <= MAZE_WIDTH/2-1 && tile->y <= MAZE_WIDTH/2-1)
					h_cost=(MAZE_WIDTH/2-1 - tile->x)+(MAZE_WIDTH/2-1 - tile->y);
				else if(tile->x <= MAZE_WIDTH/2-1 && tile->y >= MAZE_WIDTH/2)
					h_cost=(MAZE_WIDTH/2-1 - tile->x)+(tile->y - MAZE_WIDTH/2);
				else if(tile->x >= MAZE_WIDTH/2 && tile->y >= MAZE_WIDTH/2)
					h_cost=(tile->x - MAZE_WIDTH/2)+(tile->y - MAZE_WIDTH/2);
				else if(tile->x >= MAZE_WIDTH/2 && tile->y <= MAZE_WIDTH/2-1)
					h_cost=(tile->x - MAZE_WIDTH/2)+(MAZE_WIDTH/2-1 - tile->y);

				// f_cost compute
				int f_cost=g_cost+h_cost;

				tile->f_cost=f_cost;
			}
		}

		void updateCost(Tile* tile)
		{
			if(!tile->empty)
			{
				tile->dist=0; // 

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

		bool isInClosed(int x, int y)
		{	
			bool found=false;
			for(int i=0; !found && !m_closedList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(m_closedList[i].x==x && m_closedList[i].y==y)
					found=true; 
			}
			return found;
		}

		bool isInOpen(int x, int y)
		{
			bool found=false;
			for(int i=0; !found && !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(m_openList[i].x==x && m_openList[i].y==y)
					found=true; 
			}
			return found;
		}

		void addInOpen(Tile tile)
		{
			int i;
			for(i=0; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH-1; i++){} // <
			m_openList[i]=tile;
		}

		void removeOpen(int i)
		{
			m_openList[i]=vide;
			Tile back[MAZE_WIDTH*MAZE_WIDTH];
			int index_back=0;
			for(int i=0; i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(!m_openList[i].empty)
				{
					back[index_back]=m_openList[i];
					index_back++;
					m_openList[i]=vide;
				}
			}

			for(int i=0; i<index_back; i++)
			{
				m_openList[i]=back[i];
			}
		}

		void setParent(Tile* neighbour, int x, int y)
		{
			neighbour->p_x=x;
			neighbour->p_y=y;
		}

		void computeOptPath()
		{
			// search for end tile in closed
			int cp_x=-1;
			int cp_y=-1;
			for(int i=0; !m_closedList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if(m_closedList[i].x==m_end_x && m_closedList[i].y==m_end_y)
				{
					cp_x=m_closedList[i].p_x;
					cp_y=m_closedList[i].p_y;
				}

			}

			cout << "Path :" << endl;
			cout << "(" << m_end_x << "," << m_end_y << ")<-";
			cout << "(" << cp_x << "," << cp_y << ")<-";

			// follow parents	
			while(cp_x!=m_start_x || cp_y!=m_start_y)
			{
				for(int i=0; !m_closedList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
				{
					if(m_closedList[i].x==cp_x && m_closedList[i].y==cp_y)
					{
						cp_x=m_closedList[i].p_x;
						cp_y=m_closedList[i].p_y;
						cout << "(" << cp_x << "," << cp_y << ")<-";
						break;
					}
				}
			}
			cout << endl;
		}

		void explore(Maze* mazeExt)
		{
			// start tile
			Tile start;
			start.empty=false;
			start.x=m_start_x;
			start.y=m_start_y;
			start.f_cost=0;
			start.dist=0;
			start.t_cost=0;
			start.p_x=-1;
			start.p_y=-1;

			// add start node
			addInOpen(start);

			// variables
			Tile current;
			Tile neighbour[4];
			for(int i=0; i<4; i++)
				neighbour[i]=vide;
			string choix="";

			// main loop to explore
			while(1)
			{
				cout << endl << "avant" << endl;
				debug_showOpen();

				current=getOpenLowestCost();

				cout << "need to go to : ";
				debug_showTile(current);
				showMap();

				//goTo(current);
				while(choix!="o")
				{
					cin >> choix;
					if(choix=="z")
						moveUp();
					else if(choix=="d")
						moveRight();
					else if(choix=="s")
						moveDown();
					else if(choix=="q")
						moveLeft();
					showMap();
				}
				choix="";
				checkWalls(mazeExt);

				if(isDestination(current))
				{
					cout << "exploration over !" << endl;
					m_end_x=current.x;
					m_end_y=current.y;
					computeOptPath();
					break;
				}

				lookForNeighbour(neighbour); // return neighbour traversable and not in CLOSED

				debug_showNeighbour(neighbour);

				for(int i=0; !neighbour[i].empty && i<8; i++)
				{
					if(isPathShorter(current, neighbour[i]))
					{
						setParent(neighbour+i,current.x,current.y);
						setFCost(neighbour+i);
						setPath(neighbour+i);
					}
					else if(!isInOpen(neighbour[i].x, neighbour[i].y))
					{
						setParent(neighbour+i,current.x,current.y);
						setFCost(neighbour+i);
						setPath(neighbour+i);

						addInOpen(neighbour[i]);
					}
				}

				showMap();
			}
		}

		/*
		   A* algorithm
		   OPEN
		   CLOSED
		   add te start node to OPEN

		   loop
		   current = node in OPEN with the lowest f_cost
		   remove current from OPEN
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

		void debug_showOpen()
		{
			cout << "OpenList :" << endl;
			debug_showList(m_openList, 5);
		}	
		void debug_showClosed()
		{
			cout << "ClosedList :" << endl;
			debug_showList(m_closedList, 10);
		}
		void debug_showNeighbour(Tile* tiles)
		{
			cout << "Neighbours :" << endl;
			debug_showList(tiles,4);
		}
		void debug_showTile(Tile tile)
		{
			cout << endl <<  "Tile=(" << tile.x << "," << tile.y << ") empty=" << tile.empty << " f_cost=" << tile.f_cost << " dist=" << tile.dist << " t_cost=" << tile.t_cost << endl;
		}
		void debug_showList(Tile* tiles, int size)
		{
			for(int i=0; i<size; i++)
				cout << tiles[i].empty << " - (" << tiles[i].x << "," << tiles[i].y << ") f_cost=" << tiles[i].f_cost << " dist=" << tiles[i].dist << " t_cost=" << tiles[i].t_cost << " p_x=" << tiles[i].p_x << " p_y=" << tiles[i].p_y << endl;;
		}


};

#endif
