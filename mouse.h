#ifndef DEF_MOUSE
#define DEF_MOUSE

#include <iostream>
#include <unistd.h>

#include "maze.h"
#include "tile.h"

#define DIR_EMP '.'
#define DELAY_MS 500

class Mouse
{
	private:
		int m_x;
		int m_y;
		int m_last_x;
		int m_last_y;

		Tile m_start;

		int m_end_x;
		int m_end_y;

		int m_state;
		enum STATES{EXPLORE_PATH, EXPLORE_OPTI, RUN};

		Maze m_mazeInt;
		Tile m_openList[MAZE_WIDTH*MAZE_WIDTH];
		Tile m_closedList[MAZE_WIDTH*MAZE_WIDTH];

		Tile vide;

	public:
		Mouse()
		{
			m_state=EXPLORE_PATH;

			m_last_x=m_start_x;
			m_last_y=m_start_y;

			vide.empty=true;
			vide.x=-1;
			vide.y=-1;
			vide.dist=0;
			vide.g_cost=-1;
			vide.h_cost=-1;
			vide.f_cost=-1;
			vide.t_cost=-1;
			vide.p_x=-1;
			vide.p_y=-1;
			for(int i=0; i<MAZE_WIDTH*MAZE_WIDTH; i++){vide.directions[i]=DIR_EMP;}
			vide.directions[MAZE_WIDTH*MAZE_WIDTH]='\0';

			m_start=vide;
			m_start.empty=false;
			m_start.f_cost=0;
			m_start.t_cost=0;
			m_start.x=0;
			m_start.y=0;

			m_x=m_start.x;
			m_y=m_start.y;


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
			{
				for(int i=0; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
				{
					int j;
					for(j=0; m_openList[i].directions[j]!=DIR_EMP && j<MAZE_WIDTH*MAZE_WIDTH; j++){}
					m_openList[i].directions[j]='d';
				}
				m_last_x=m_x;
				m_x++;
			}
		}
		void moveDown()
		{
			if(m_mazeInt.getWallDown(m_x,m_y)==0)
			{
				for(int i=0; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
				{
					int j;
					for(j=0; m_openList[i].directions[j]!=DIR_EMP && j<MAZE_WIDTH*MAZE_WIDTH; j++){}
					m_openList[i].directions[j]='u';
				}
				m_last_x=m_x;
				m_x--;
			}
		}
		void moveRight()
		{
			if(m_mazeInt.getWallRight(m_x,m_y)==0)
			{
				for(int i=0; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
				{
					int j;
					for(j=0; m_openList[i].directions[j]!=DIR_EMP && j<MAZE_WIDTH*MAZE_WIDTH; j++){}
					m_openList[i].directions[j]='l';
				}
				m_last_y=m_y;
				m_y++;
			}
		}
		void moveLeft()
		{
			if(m_mazeInt.getWallLeft(m_x,m_y)==0)
			{
				for(int i=0; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
				{
					int j;
					for(j=0; m_openList[i].directions[j]!=DIR_EMP && j<MAZE_WIDTH*MAZE_WIDTH; j++){}
					m_openList[i].directions[j]='r';
				}
				m_last_y=m_y;
				m_y--;
			}
		}

		Tile getOpenLowestCost()
		{

			// search for lowest cost tile // add distance from itself
			int i_min=0;
			int cost_min=m_openList[0].t_cost;
			int dist=m_openList[0].dist;
			for(int i=1; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				if((m_openList[i].t_cost<cost_min)
						|| (m_openList[i].t_cost==cost_min && m_openList[i].dist<dist))
				{
					i_min=i;
					cost_min=m_openList[i].t_cost;
					dist=m_openList[i].dist;
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
			// found first
			int index=-1;
			for(index=0; tile.directions[index]!=DIR_EMP && index<=MAZE_WIDTH*MAZE_WIDTH; index++){}
			index--;

			char dir;
			while(index>=0)
			{
				dir=tile.directions[index];

				if(dir=='u')
					moveUp();
				else if(dir=='r')
					moveRight();
				else if(dir=='d')
					moveDown();
				else if(dir=='l')
					moveLeft();
				showMap();
				index--;
				usleep(DELAY_MS*1000/2);
			}
		}

		void manualGoTo()
		{
			string choix="";
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
				neighbour[index].directions[0]='u';
				index++;
			}
			if(!m_mazeInt.getWallDown(m_x,m_y)
					&& !isInClosed(m_x-1, m_y))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x-1;
				neighbour[index].y=m_y;
				neighbour[index].directions[0]='d';
				index++;
			}
			if(!m_mazeInt.getWallRight(m_x,m_y)
					&& !isInClosed(m_x, m_y+1))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x;
				neighbour[index].y=m_y+1;
				neighbour[index].directions[0]='r';
				index++;
			}
			if(!m_mazeInt.getWallLeft(m_x,m_y)
					&& !isInClosed(m_x, m_y-1))
			{
				neighbour[index].empty=false;
				neighbour[index].x=m_x;
				neighbour[index].y=m_y-1;
				neighbour[index].directions[0]='l';
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
				while(cp_x!=m_start.x || cp_y!=m_start.y)
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
				tile->g_cost=g_cost;

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
				tile->h_cost=h_cost;

				// f_cost compute
				tile->f_cost = tile->g_cost + tile->h_cost;
			}
		}

		void updateCosts()
		{
			int dist=0;

			// clean des directions
			bool erreur;
			int index_last_dir;
			for(int i=0; !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++)
			{
				erreur=false;
				dist=0;

				index_last_dir=0;
				// u r r u l r d r d
				// u r r u     d r d
				// u r r         r d
				for(int j=1; m_openList[i].directions[j]!=DIR_EMP && i<MAZE_WIDTH*MAZE_WIDTH; j++)
				{
					if((m_openList[i].directions[j]=='u' && m_openList[i].directions[index_last_dir]=='d')
					||(m_openList[i].directions[j]=='d' && m_openList[i].directions[index_last_dir]=='u')
					||(m_openList[i].directions[j]=='r' && m_openList[i].directions[index_last_dir]=='l')
					||(m_openList[i].directions[j]=='l' && m_openList[i].directions[index_last_dir]=='r'))
					{
						erreur=true;
						m_openList[i].directions[j]=DIR_EMP;
						m_openList[i].directions[index_last_dir]=DIR_EMP;
						index_last_dir--;
					}
					else
						index_last_dir++;
					while(m_openList[i].directions[index_last_dir]==DIR_EMP && index_last_dir<MAZE_WIDTH*MAZE_WIDTH)
						index_last_dir++;
				}
				if(erreur)
				{
					char back_dir[MAZE_WIDTH*MAZE_WIDTH];
					for(int j=0; j<MAZE_WIDTH*MAZE_WIDTH; j++){back_dir[j]=DIR_EMP;}
					int index=0;

					// clean
					for(int k=0; k<MAZE_WIDTH*MAZE_WIDTH; k++)
					{
						if(m_openList[i].directions[k]!=DIR_EMP)
						{
							back_dir[index]=m_openList[i].directions[k];
							m_openList[i].directions[k]=DIR_EMP;
							index++;
						}
					}
					for(int j=0; j<index; j++)
						m_openList[i].directions[j]=back_dir[j];
				}

				// calcul dist
				for(int j=0; m_openList[i].directions[j]!=DIR_EMP && j<MAZE_WIDTH*MAZE_WIDTH; j++)
					dist++;
				m_openList[i].dist=dist;

				// update cost
				m_openList[i].t_cost=m_openList[i].f_cost+m_openList[i].dist;
			}
		}

		bool isPathShorter(int current_g, int neigh_x, int neigh_y)
		{
			int i;
			for(i=0; (m_openList[i].x!=neigh_x || m_openList[i].y!=neigh_y) && !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++){}
			int neighbour_g=m_openList[i].g_cost;
			if(current_g+1<neighbour_g)
				return true;
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
			while(cp_x!=m_start.x || cp_y!=m_start.y)
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

		void replaceInOpen(Tile tile)
		{
			int i;
			for(i=0; (m_openList[i].x!=tile.x || m_openList[i].y!=tile.y) && !m_openList[i].empty && i<MAZE_WIDTH*MAZE_WIDTH; i++){}

			m_openList[i]=tile;
		}

		void explore(Maze* mazeExt)
		{
			// add start node
			addInOpen(m_start);

			// variables
			Tile current;
			Tile neighbour[4];
			for(int i=0; i<4; i++)
				neighbour[i]=vide;

			// main loop to explore
			while(1)
			{
				cout << endl << "main loop" << endl;

				debug_showOpen();
				current=getOpenLowestCost();

				cout << "need to go to : ";
				debug_showTile(current);
				showMap();

				goTo(current);
				//manualGoTo();

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
					if(!isInOpen(neighbour[i].x, neighbour[i].y))
					{
						setParent(neighbour+i,current.x,current.y);
						setFCost(neighbour+i);

						addInOpen(neighbour[i]);
					}	
					else if(isPathShorter(current.g_cost, neighbour[i].x, neighbour[i].y))
					{
						setParent(neighbour+i,current.x,current.y);
						setFCost(neighbour+i);

						replaceInOpen(neighbour[i]);
					}
				}
				updateCosts();

				showMap();
				usleep(DELAY_MS*1000);
			}
		}

		void FSM(Maze* mazeExt)
		{
			switch(m_state)
			{
				case EXPLORE_PATH:
					explore(mazeExt);
					m_state=EXPLORE_OPTI;
					break;
				case EXPLORE_OPTI:
					cout << "hum c'est surement opti" << endl;
					usleep(DELAY_MS*10000);
					break;
				case RUN:
					break;
			}
		}

		void debug_showOpen()
		{
			cout << "OpenList :" << endl;
			debug_showList(m_openList, 5, true);
		}
		void debug_showClosed()
		{
			cout << "ClosedList :" << endl;
			debug_showList(m_closedList, 10, true);
		}
		void debug_showNeighbour(Tile* tiles)
		{
			cout << "Neighbours :" << endl;
			debug_showList(tiles,4,false);
		}
		void debug_showTile(Tile tile)
		{
			cout << endl <<  "Tile=(" << tile.x << "," << tile.y << ") empty=" << tile.empty << " f_cost=" << tile.f_cost << " dist=" << tile.dist << " t_cost=" << tile.t_cost << endl;
		}
		void debug_showList(Tile* tiles, int size, bool full)
		{
			for(int i=0; i<size; i++)
			{
				if(!tiles[i].empty)
				{
					cout << tiles[i].empty << " - (" << tiles[i].x << "," << tiles[i].y << ")";
					if(full)
						cout << " f_cost=" << tiles[i].f_cost << " dist=" << tiles[i].dist << " t_cost=" << tiles[i].t_cost << endl << "\tdirection:" << tiles[i].directions << " p=(" << tiles[i].p_x << "," << tiles[i].p_y << ")";
					cout << endl;
				}
			}
		}
};

#endif
