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
		// Vertical walls
		for(int i=0; i<MAZE_WIDTH; i++)
		{
			m_walls_v[i][0]=true;
			for(int j=1; j<MAZE_WIDTH+1-1; j++)
				m_walls_v[i][j]=false;
			m_walls_v[i][MAZE_WIDTH]=true;
		}
		// Horizontal walls
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
