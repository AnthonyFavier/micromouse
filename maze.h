#ifndef DEF_MAZE
#define DEF_MAZE

#define MAZE_WIDTH 10
#define TILE_WIDTH 10

#include <iostream>

using namespace std;

class Maze
{
	private:
		int m_walls_v[MAZE_WIDTH][MAZE_WIDTH+1];
		int m_walls_h[MAZE_WIDTH+1][MAZE_WIDTH];
	public:
		Maze()
		{
			for(int i=0; i<MAZE_WIDTH; i++)
			{
				for(int j=0; j<MAZE_WIDTH+1; j++)
					m_walls_v[i][j]=8;
			}	
			for(int i=0; i<MAZE_WIDTH+1; i++)
			{
				for(int j=0; j<MAZE_WIDTH; j++)
					m_walls_h[i][j]=8;
			}

		}

		void draw()
		{
			// Init empty
			//// Vertical walls
			for(int i=0; i<MAZE_WIDTH; i++)
			{
				m_walls_v[i][0]=1;
				for(int j=1; j<MAZE_WIDTH+1-1; j++)
					m_walls_v[i][j]=0;
				m_walls_v[i][MAZE_WIDTH]=1;
			}
			//// Horizontal walls
			for(int j=0; j<MAZE_WIDTH; j++)
			{
				m_walls_h[0][j]=1;
				for(int i=1; i<MAZE_WIDTH+1-1; i++)
					m_walls_h[i][j]=0;
				m_walls_h[MAZE_WIDTH][j]=1;
			}

			// Draw maze
			m_walls_v[0][8]=1;
			m_walls_v[1][8]=1;
			m_walls_v[2][8]=1;
			m_walls_v[3][8]=1;
			m_walls_v[4][8]=1;

		}

		int getWallDown(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				return m_walls_h[x][y];
			else
			{
				cout << "ERREUR: getWallDown: x,y out of bound" << endl;
				return true;
			}
		}
		int getWallUp(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				return m_walls_h[x+1][y];
			else
			{
				cout << "ERREUR: getWallUp: x,y out of bound" << endl;
				return true;
			}
		}
		int getWallLeft(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				return m_walls_v[x][y];
			else
			{
				cout << "ERREUR: getWallLeft: x,y out of bound" << endl;
				return true;
			}
		}
		int getWallRight(int x, int y)
		{
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				return m_walls_v[x][y+1];
			else
			{
				cout << "ERREUR: getWallRight: x,y out of bound" << endl;
				return true;
			}
		}

		void setWallDown(int x, int y, int wall)
		{	
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				m_walls_h[x][y]=wall;
			else
				cout << "ERREUR: setWallDown: x,y out of bound" << endl;
		}
		void setWallUp(int x, int y, int wall)
		{	
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				m_walls_h[x+1][y]=wall;
			else
				cout << "ERREUR: setWallUp: x,y out of bound" << endl;
		}
		void setWallLeft(int x, int y, int wall)
		{	
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				m_walls_v[x][y]=wall;
			else
				cout << "ERREUR: setWallLeft: x,y out of bound" << endl;
		}
		void setWallRight(int x, int y, int wall)
		{	
			if(x>=0 && x<MAZE_WIDTH && y>=0 && y<MAZE_WIDTH)
				m_walls_v[x][y+1]=wall;
			else
				cout << "ERREUR: setWallRight: x,y out of bound" << endl;
		}

		void show()
		{
			cout << endl;
			// Top horizontal
			cout << "  ";
			for(int j=0; j<MAZE_WIDTH; j++)
				cout << m_walls_h[MAZE_WIDTH][j] << "   ";
			cout << endl;

			// Middle
			for(int i=MAZE_WIDTH-1; i>=0; i--)
			{	
				// Vertical walls
				for(int j=0; j<MAZE_WIDTH+1; j++)
				{
					cout << m_walls_v[i][j];
					if(j!=MAZE_WIDTH)
						cout << " ¤ ";
				}
				cout << endl;

				// Horizontal walls (expect bot and top)
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

			// Bot horizontal
			cout << "  ";
			for(int j=0; j<MAZE_WIDTH; j++)
				cout << m_walls_h[0][j] << "   ";
			cout << endl;

		}

		void show(int x, int y)
		{
			cout << endl;
			// Top horizontal
			cout << "  ";
			for(int j=0; j<MAZE_WIDTH; j++)
				cout << m_walls_h[MAZE_WIDTH][j] << "   ";
			cout << endl;

			// Middle
			for(int i=MAZE_WIDTH-1; i>=0; i--)
			{	
				// Vertical walls
				for(int j=0; j<MAZE_WIDTH+1; j++)
				{
					cout << m_walls_v[i][j];
					if(j!=MAZE_WIDTH)
					{
						if(i==x && j==y)
							cout << " X ";
						else
							cout << " ¤ ";
					}
				}
				cout << endl;

				// Horizontal walls (expect bot and top)
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

			// Bot horizontal
			cout << "  ";
			for(int j=0; j<MAZE_WIDTH; j++)
				cout << m_walls_h[0][j] << "   ";
			cout << endl;

		}

};

#endif
