

#include "../../include/cub3d.h"
#include "../../libft/libft.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define DOT_SIZE 10
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364
#define ESC 65307
#define TILE_SIZE 64
#define MAP_CELL 8

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		map[MAP_CELL][MAP_CELL];
	int		x;
	int		y;
}			t_data;

#define WALL_COLOR 0x000000 // black for 1
#define FLOOR_COLOR 0xFFFFFF // white for 0
#define GRID_COLOR 0x888888 // optional: gray grid lines
#define CURSOR_COLOR 0xFF0000 // e.g. red cursor

void	draw_tile(t_data *data, int x0, int y0, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			mlx_pixel_put(data->mlx, data->win, x0 + j, y0 + i, color);
			j++;
		}
		i++;
	}
}

static void	redraw(t_data *d)
{
	int row, col;
	int x0, y0;
	mlx_clear_window(d->mlx, d->win);
	/* draw floor & walls */
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
	/* draw grid lines (optional) */
	for (row = 0; row <= MAP_CELL; row++)
		for (col = 0; col < MAP_CELL * TILE_SIZE; col++)
			mlx_pixel_put(d->mlx, d->win, col, row * TILE_SIZE, GRID_COLOR);
	for (col = 0; col <= MAP_CELL; col++)
		for (row = 0; row < MAP_CELL * TILE_SIZE; row++)
			mlx_pixel_put(d->mlx, d->win, col * TILE_SIZE, row, GRID_COLOR);
	/* draw cursor highlight */
	x0 = d->x * TILE_SIZE;
	y0 = d->y * TILE_SIZE;
	for (int i = 0; i < TILE_SIZE; i++)
	{
		mlx_pixel_put(d->mlx, d->win, x0 + i, y0, CURSOR_COLOR);
		mlx_pixel_put(d->mlx, d->win, x0 + i, y0 + TILE_SIZE - 1, CURSOR_COLOR);
		mlx_pixel_put(d->mlx, d->win, x0, y0 + i, CURSOR_COLOR);
		mlx_pixel_put(d->mlx, d->win, x0 + TILE_SIZE - 1, y0 + i, CURSOR_COLOR);
	}
}

void	draw_dot(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(data->mlx, data->win, data->x + j, data->y + i,
				0xFF0000);
			j++;
		}
		i++;
	}
}

int	key_hook(int keycode, t_data *d)
{
	int	new_x;
	int	new_y;

	new_x = d->x;
	new_y = d->y;
	int tx1, ty1, tx2, ty2;
	if (keycode == LEFT)
		new_x -= DOT_SIZE;
	else if (keycode == RIGHT)
		new_x += DOT_SIZE;
	else if (keycode == UP)
		new_y -= DOT_SIZE;
	else if (keycode == DOWN)
		new_y += DOT_SIZE;
	else if (keycode == ESC)
		exit(0);
	else
		return (0);
	/* Decide which two points to test, depending on direction */
	if (keycode == LEFT || keycode == RIGHT)
	{
		/* same vertical span: top and bottom of the dot */
		ty1 = new_y / TILE_SIZE;
		ty2 = (new_y + DOT_SIZE - 1) / TILE_SIZE;
		if (keycode == LEFT)
			tx1 = tx2 = new_x / TILE_SIZE;
		else /* RIGHT */
			tx1 = tx2 = (new_x + DOT_SIZE - 1) / TILE_SIZE;
	}
	else /* UP or DOWN */
	{
		/* same horizontal span: left and right of the dot */
		tx1 = new_x / TILE_SIZE;
		tx2 = (new_x + DOT_SIZE - 1) / TILE_SIZE;
		if (keycode == UP)
			ty1 = ty2 = new_y / TILE_SIZE;
		else /* DOWN */
			ty1 = ty2 = (new_y + DOT_SIZE - 1) / TILE_SIZE;
	}
	/* Bounds check */
	if (tx1 < 0 || tx1 >= MAP_CELL || tx2 < 0 || tx2 >= MAP_CELL || ty1 < 0
		|| ty1 >= MAP_CELL || ty2 < 0 || ty2 >= MAP_CELL)
	{
		/* out of map—don’t move */
	}
	else
	{
		/* only move if both target tiles are floor (0) */
		if (d->map[ty1][tx1] == 0 && d->map[ty2][tx2] == 0)
		{
			d->x = new_x;
			d->y = new_y;
		}
	}
	/* redraw */
	mlx_clear_window(d->mlx, d->win);
	redraw(d);
	draw_dot(d);
	return (0);
}


// int	main(void)
// {
// 	t_data data;
// 	data.mlx = mlx_init();
// 	data.win = mlx_new_window(data.mlx, MAP_CELL * TILE_SIZE, MAP_CELL
// 			* TILE_SIZE, "Hello world!");
// 	data.x = WIN_WIDTH / 2;
// 	data.y = WIN_HEIGHT / 2;
// 	set_map(&data);
// 	redraw(&data);
// 	mlx_key_hook(data.win, key_hook, &data);
// 	mlx_loop(data.mlx);
// 	return (0);
// }