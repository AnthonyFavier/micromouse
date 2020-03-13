#ifndef DEF_TILE
#define DEF_TILE

struct Tile
{
	int f_cost;
	int dist;
	int t_cost;
	int x;
	int y;
	bool empty;
	int p_x;
	int p_y;
};

#endif
