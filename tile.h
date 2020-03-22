#ifndef DEF_TILE
#define DEF_TILE

#define MAZE_WIDTH 6
// Pair !!!

struct Tile
{
	int g_cost;
	int h_cost;
	int f_cost;
	int dist;
	int t_cost;
	int x;
	int y;
	bool empty;
	int p_x;
	int p_y;
	char directions[MAZE_WIDTH*MAZE_WIDTH+1];
};

#endif
