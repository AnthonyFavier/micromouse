#ifndef DEF_MAZE
#define DEF_MAZE

#define MAZE_WIDTH 10
#define TILE_WIDTH 10

#include <iostream>

using namespace std;

class Maze
{
	private:
		bool m_walls_v[MAZE_WIDTH][MAZE_WIDTH+1];
		bool m_walls_h[MAZE_WIDTH+1][MAZE_WIDTH];
	public:
		Maze()
		{
			// Init empty
			//// Vertical walls
			for(int i=0; i<MAZE_WIDTH; i++)
			{
				m_walls_v[i][0]=true;
				for(int j=1; j<MAZE_WIDTH+1-1; j++)
					m_walls_v[i][j]=false;
				m_walls_v[i][MAZE_WIDTH]=true;
			}
			//// Horizontal walls
			for(int j=0; j<MAZE_WIDTH; j++)
			{
				m_walls_h[0][j]=true;
				for(int i=1; i<MAZE_WIDTH+1-1; i++)
					m_walls_h[i][j]=false;
				m_walls_h[MAZE_WIDTH][j]=true;
			}

			// Draw maze
			m_walls_v[0][8]=true;
			m_walls_v[1][8]=true;
			m_walls_v[2][8]=true;
			m_walls_v[3][8]=true;
			m_walls_v[4][8]=true;
		}

		bool getWallDown(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				return m_walls_h[x][y];
			else
			{
				cout << "ERREUR: getWallDown: x,y out of bound" << endl;
				return true;
			}
		}
		bool getWallUp(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				return m_walls_h[x][y+1];
			else
			{
				cout << "ERREUR: getWallUp: x,y out of bound" << endl;
				return true;
			}
		}
		bool getWallLeft(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				return m_walls_v[x][y];
			else
			{
				cout << "ERREUR: getWallLeft: x,y out of bound" << endl;
				return true;
			}
		}
		bool getWallRight(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				return m_walls_v[x+1][y];
			else
			{
				cout << "ERREUR: getWallRight: x,y out of bound" << endl;
				return true;
			}
		}

		void setWallDown(int x, int y, bool wall)
		{	
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				m_walls_h[x][y]=wall;
			else
				cout << "ERREUR: setWallDown: x,y out of bound" << endl;
		}
		void setWallUp(int x, int y, bool wall)
		{	
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				m_walls_h[x][y+1]=wall;
			else
				cout << "ERREUR: setWallUp: x,y out of bound" << endl;
		}
		void setWallLeft(int x, int y, bool wall)
		{	
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				m_walls_v[x][y]=wall;
			else
				cout << "ERREUR: setWallLeft: x,y out of bound" << endl;
		}
		void setWallRight(int x, int y, bool wall)
		{	
			if(x>=0 && x<MAZE_WIDTH-1 && y>=0 && y<MAZE_WIDTH-1)
				m_walls_v[x+1][y]=wall;
			else
				cout << "ERREUR: setWallRight: x,y out of bound" << endl;
		}

		void show()
		{
			cout << "  ";
			for(int j=0; j<MAZE_WIDTH; j++)
				cout << m_walls_h[MAZE_WIDTH][j] << "   ";
			cout << endl;

			for(int i=MAZE_WIDTH-1; i>=0; i--)
			{	
				for(int j=0; j<MAZE_WIDTH+1; j++)
				{
					cout << m_walls_v[i][j];
					if(j!=MAZE_WIDTH)
						cout << " ¤ ";
				}
				cout << endl;

				if(i!=0)
				{
					cout << "  ";
					for(int j=0; j<MAZE_WIDTH; j++)
					{
						cout << m_walls_h[i][j];
						if(j!=MAZE_WIDTH-1)
							cout << "   ";
					}
					cout << endl;
				}
			}

			cout << "  ";
			for(int j=0; j<MAZE_WIDTH; j++)
				cout << m_walls_h[0][j] << "   ";
			cout << endl;

		}
};

#endif
