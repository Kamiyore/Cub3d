

// #include "../../include/cub3d.h"
// #include "../../libft/libft.h"

// #define WIN_WIDTH 800
// #define WIN_HEIGHT 600
// #define DOT_SIZE 8
// #define LEFT 65361
// #define RIGHT 65363
// #define UP 65362
// #define DOWN 65364
// #define ESC 65307
// #define TILE_SIZE 64
// #define MAP_CELL 8

// // MATH
// #define PI 3.14159265359

// typedef struct s_cub_data
// {
// 	void	*mlx;
// 	void	*win;
// 	int		map[MAP_CELL][MAP_CELL];
// 	int		x;
// 	int		y;
// 	float	pdx;
// 	float	pdy;
// 	float	pa;
// }			t_cub;

// #define WALL_COLOR 0x000000 // black for 1
// #define FLOOR_COLOR 0xFFFFFF // white for 0
// #define GRID_COLOR 0x888888 // optional: gray grid lines
// #define CURSOR_COLOR 0xFF0000 // e.g. red cursor

// void	draw_tile(t_cub *cub, int x0, int y0, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			mlx_pixel_put(cub->mlx, cub->win, x0 + j, y0 + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// static void	redraw(t_cub *d)
// {
// 	int row, col;
// 	int x0, y0;
// 	mlx_clear_window(d->mlx, d->win);
// 	/* draw floor & walls */
// 	for (row = 0; row < MAP_CELL; row++)
// 	{
// 		for (col = 0; col < MAP_CELL; col++)
// 		{
// 			x0 = col * TILE_SIZE;
// 			y0 = row * TILE_SIZE;
// 			if (d->map[row][col] == 1)
// 				draw_tile(d, x0, y0, WALL_COLOR);
// 			else
// 				draw_tile(d, x0, y0, FLOOR_COLOR);
// 		}
// 	}
// 	/* draw grid lines (optional) */
// 	for (row = 0; row <= MAP_CELL; row++)
// 		for (col = 0; col < MAP_CELL * TILE_SIZE; col++)
// 			mlx_pixel_put(d->mlx, d->win, col, row * TILE_SIZE, GRID_COLOR);
// 	for (col = 0; col <= MAP_CELL; col++)
// 		for (row = 0; row < MAP_CELL * TILE_SIZE; row++)
// 			mlx_pixel_put(d->mlx, d->win, col * TILE_SIZE, row, GRID_COLOR);
// 	/* draw cursor highlight */
// 	x0 = d->x * TILE_SIZE;
// 	y0 = d->y * TILE_SIZE;
// 	for (int i = 0; i < TILE_SIZE; i++)
// 	{
// 		mlx_pixel_put(d->mlx, d->win, x0 + i, y0, CURSOR_COLOR);
// 		mlx_pixel_put(d->mlx, d->win, x0 + i, y0 + TILE_SIZE - 1, CURSOR_COLOR);
// 		mlx_pixel_put(d->mlx, d->win, x0, y0 + i, CURSOR_COLOR);
// 		mlx_pixel_put(d->mlx, d->win, x0 + TILE_SIZE - 1, y0 + i, CURSOR_COLOR);
// 	}
// }

// void	draw_dot(t_cub *cub)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < 10)
// 	{
// 		j = 0;
// 		while (j < 10)
// 		{
// 			mlx_pixel_put(cub->mlx, cub->win, cub->x + j, cub->y + i, 0xFF0000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// int	key_hook(int keycode, t_cub *cub)
// {
// 	int	new_x;
// 	int	new_y;

// 	new_x = cub->x;
// 	new_y = cub->y;
// 	int tx1, ty1, tx2, ty2;
// 	if (keycode == LEFT)
// 		new_x -= DOT_SIZE;
// 	else if (keycode == RIGHT)
// 		new_x += DOT_SIZE;
// 	else if (keycode == UP)
// 		new_y -= DOT_SIZE;
// 	else if (keycode == DOWN)
// 		new_y += DOT_SIZE;
// 	else if (keycode == ESC)
// 		exit(0);
// 	else
// 		return (0);
// 	/* Decide which two points to test, depending on direction */
// 	if (keycode == LEFT)
// 	{
// 		cub->pa -= 0.1;
// 		if (cub->pa < 0)
// 			cub->pa += 2 * PI;
// 		cub->pdx = cos(cub->pa) * DOT_SIZE;
// 		cub->pdy = sin(cub->pa) * DOT_SIZE;
// 	}
// 	else if (keycode == RIGHT)
// 	{
// 		cub->pa += 0.1;
// 		if (cub->pa > 2 * PI)
// 			cub->pa -= 2 * PI;
// 		cub->pdx = cos(cub->pa) * DOT_SIZE;
// 		cub->pdy = sin(cub->pa) * DOT_SIZE;
// 	}
// 	else /* UP or DOWN */
// 	{
// 		/* same horizontal span: left and right of the dot */
// 		tx1 = new_x / TILE_SIZE;
// 		tx2 = (new_x + DOT_SIZE - 1) / TILE_SIZE;
// 		if (keycode == UP)
// 			ty1 = ty2 = new_y / TILE_SIZE;
// 		else /* DOWN */
// 			ty1 = ty2 = (new_y + DOT_SIZE - 1) / TILE_SIZE;
// 	}
// 	/* Bounds check */
// 	if (tx1 < 0 || tx1 >= MAP_CELL || tx2 < 0 || tx2 >= MAP_CELL || ty1 < 0
// 		|| ty1 >= MAP_CELL || ty2 < 0 || ty2 >= MAP_CELL)
// 	{
// 		/* out of map—don’t move */
// 	}
// 	else
// 	{
// 		/* only move if both target tiles are floor (0) */
// 		if (cub->map[ty1][tx1] == 0 && cub->map[ty2][tx2] == 0)
// 		{
// 			cub->x = new_x;
// 			cub->y = new_y;
// 		}
// 	}
// 	/* redraw */
// 	mlx_clear_window(cub->mlx, cub->win);
// 	redraw(cub);
// 	draw_dot(cub);
// 	return (0);
// }

// void	set_map(t_cub *cub)
// {
// 	static const int literal[MAP_CELL][MAP_CELL] = {
// 		{1, 1, 1, 1, 1, 1, 1, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 0, 0, 0, 0, 0, 0, 1},
// 		{1, 1, 1, 1, 1, 1, 1, 1},
// 	};
// 	ft_memcpy(cub->map, literal, sizeof(literal));
// }

// int	main(void)
// {
// 	t_cub	cub;

// 	cub.mlx = mlx_init();
// 	cub.win = mlx_new_window(cub.mlx, MAP_CELL * TILE_SIZE, MAP_CELL
// 			* TILE_SIZE, "Hello world!");
// 	cub.x = WIN_WIDTH / 2;
// 	cub.y = WIN_HEIGHT / 2;
// 	cub.pdx = 0;
// 	cub.pdy = 0;
// 	cub.pa = 0;
// 	set_map(&cub);
// 	redraw(&cub);
// 	mlx_key_hook(cub.win, key_hook, &cub);
// 	mlx_loop(cub.mlx);
// 	return (0);
// }

#include "../../include/cub3d.h"
#include "../../libft/libft.h"
#include <math.h> // for cos() and sin()

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define DOT_SIZE 8 // used for movement increment
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364
#define ESC 65307
#define TILE_SIZE 64
#define MAP_CELL 8

// MATH
#define PI 3.14159265359

typedef struct s_cub_data
{
	void	*mlx;
	void	*win;
	int		map[MAP_CELL][MAP_CELL];
	int x;     // dot’s top-left pixel x-position
	int y;     // dot’s top-left pixel y-position
	float pdx; // step in x (for forward movement)
	float pdy; // step in y (for forward movement)
	float pa;  // current angle (radians)
}			t_cub;

#define WALL_COLOR 0x000000 // black for wall (1)
#define FLOOR_COLOR 0xFFFFFF // white for floor (0)
#define GRID_COLOR 0x888888 // gray grid lines

/* Draws a square of TILE_SIZE x TILE_SIZE starting at (x0,y0) */
void	draw_tile(t_cub *cub, int x0, int y0, int color)
{
	int i, j;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(cub->mlx, cub->win, x0 + j, y0 + i, color);
			j++;
		}
		i++;
	}
}

/* Redraws the floor, walls, grid and highlights the current cell */
static void	redraw(t_cub *d)
{
	int row, col;
	int x0, y0;
	mlx_clear_window(d->mlx, d->win);
	/* Draw floor & walls */
	for (row = 0; row < MAP_CELL; row++)
	{
		for (col = 0; col < MAP_CELL; col++)
		{
			x0 = col * TILE_SIZE;
			y0 = row * TILE_SIZE;
			if (d->map[row][col] == 1)
				draw_tile(d, x0, y0, WALL_COLOR);
			else
				draw_tile(d, x0, y0, FLOOR_COLOR);
		}
	}
	/* Draw grid lines (optional) */
	for (row = 0; row <= MAP_CELL; row++)
		for (col = 0; col < MAP_CELL * TILE_SIZE; col++)
			mlx_pixel_put(d->mlx, d->win, col, row * TILE_SIZE, GRID_COLOR);
	for (col = 0; col <= MAP_CELL; col++)
		for (row = 0; row < MAP_CELL * TILE_SIZE; row++)
			mlx_pixel_put(d->mlx, d->win, col * TILE_SIZE, row, GRID_COLOR);
	/* Draw a cell highlight (red border) around the cell in which the dot is */
	x0 = d->x / TILE_SIZE * TILE_SIZE;
	y0 = d->y / TILE_SIZE * TILE_SIZE;
}

/* Draws the dot (the player) as a 10×10 red square */
void	draw_dot(t_cub *cub)
{
	int i, j;
	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(cub->mlx, cub->win, cub->x + j, cub->y + i, 0xFF0000);
			j++;
		}
		i++;
	}
}

/* Draws an arrow starting at the center of the dot showing its facing direction */
void	draw_arrow(t_cub *cub)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	int center_x, center_y;
	int arrow_length = 20; // adjust arrow length as needed
	int end_x, end_y;
	// Compute the center of the 10x10 dot.
	center_x = cub->x + 5;
	center_y = cub->y + 5;
	// Compute the end point of the arrow using the current angle.
	end_x = center_x + (int)(cos(cub->pa) * arrow_length);
	end_y = center_y + (int)(sin(cub->pa) * arrow_length);
	/* Simple DDA line drawing algorithm */
	dx = end_x - center_x;
	dy = end_y - center_y;
	steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = center_x;
	y = center_y;
	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(cub->mlx, cub->win, (int)x, (int)y, 0x0000FF);
		// blue arrow
		x += x_inc;
		y += y_inc;
	}
}

/* The key_hook is now split between rotation (left/right) and movement (up/down)
   LEFT and RIGHT update the angle (pa) and recompute the directional vector (pdx,
	pdy).
   UP moves the dot forward in the direction of pdx, pdy.
   DOWN moves backwards.
*/
int	key_hook(int keycode, t_cub *cub)
{
	int new_x, new_y;
	int tx1, ty1, tx2, ty2;
	new_x = cub->x;
	new_y = cub->y;
	if (keycode == LEFT)
	{
		cub->pa -= 0.1;
		if (cub->pa < 0)
			cub->pa += 2 * PI;
		cub->pdx = cos(cub->pa) * DOT_SIZE;
		cub->pdy = sin(cub->pa) * DOT_SIZE;
	}
	else if (keycode == RIGHT)
	{
		cub->pa += 0.1;
		if (cub->pa > 2 * PI)
			cub->pa -= 2 * PI;
		cub->pdx = cos(cub->pa) * DOT_SIZE;
		cub->pdy = sin(cub->pa) * DOT_SIZE;
	}
	else if (keycode == UP)
	{
		new_x += (int)(cub->pdx);
		new_y += (int)(cub->pdy);
		tx1 = new_x / TILE_SIZE;
		tx2 = (new_x + 10 - 1) / TILE_SIZE;
		ty1 = new_y / TILE_SIZE;
		ty2 = (new_y + 10 - 1) / TILE_SIZE;
		if (tx1 >= 0 && tx2 < MAP_CELL && ty1 >= 0 && ty2 < MAP_CELL)
		{
			if (cub->map[ty1][tx1] == 0 && cub->map[ty2][tx2] == 0)
			{
				cub->x = new_x;
				cub->y = new_y;
			}
		}
	}
	else if (keycode == DOWN)
	{
		new_x -= (int)(cub->pdx);
		new_y -= (int)(cub->pdy);
		tx1 = new_x / TILE_SIZE;
		tx2 = (new_x + 10 - 1) / TILE_SIZE;
		ty1 = new_y / TILE_SIZE;
		ty2 = (new_y + 10 - 1) / TILE_SIZE;
		if (tx1 >= 0 && tx2 < MAP_CELL && ty1 >= 0 && ty2 < MAP_CELL)
		{
			if (cub->map[ty1][tx1] == 0 && cub->map[ty2][tx2] == 0)
			{
				cub->x = new_x;
				cub->y = new_y;
			}
		}
	}
	else if (keycode == ESC)
		exit(0);
	mlx_clear_window(cub->mlx, cub->win);
	redraw(cub);
	draw_dot(cub);
	draw_arrow(cub);
	return (0);
}

/* Copy a static literal into the map array */
void	set_map(t_cub *cub)
{
	static const int literal[MAP_CELL][MAP_CELL] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
	};
	ft_memcpy(cub->map, literal, sizeof(literal));
}

int	main(void)
{
	t_cub	cub;

	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, MAP_CELL * TILE_SIZE, MAP_CELL
			* TILE_SIZE, "Hello world!");
	/* Start the dot near the center of a floor cell.
		Here, we use WIN_WIDTH/2 and WIN_HEIGHT/2 only as initial values;
		you might prefer to choose something that lies on a floor (0) cell. */
	cub.x = WIN_WIDTH / 2;
	cub.y = WIN_HEIGHT / 2;
	cub.pa = 0; // initial angle is 0 radians (facing to the right)
	cub.pdx = cos(cub.pa) * DOT_SIZE;
	cub.pdy = sin(cub.pa) * DOT_SIZE;
	set_map(&cub);
	redraw(&cub);
	draw_dot(&cub);
	draw_arrow(&cub);
	mlx_key_hook(cub.win, key_hook, &cub);
	mlx_loop(cub.mlx);
	return (0);
}
