
#include "../../include/cub3d.h"
#include "../../libft/libft.h"
#include <math.h> // for cos(), sin(), fabs()

/*========================================================================
  Window & input definitions
  ------------------------------------------------------------------------
  WIN_WIDTH / WIN_HEIGHT: initial start‐position references (not actually
	used for window size here, but for centering logic)
  DOT_SIZE: movement increment per keypress or step
  LEFT/RIGHT/UP/DOWN/ESC: X11 keycodes for arrow keys & Escape
  TILE_SIZE: size in pixels of each map square
  MAP_CELL: number of cells per row/column in your 8×8 map
  PI: mathematical constant π
  ========================================================================*/
#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define DOT_SIZE 8
#define DOT_DIM 10 // size (in px) of the drawn dot
#define LEFT 65361
#define RIGHT 65363
#define UP 65362
#define DOWN 65364
#define ESC 65307
#define TILE_SIZE 64
#define MAP_CELL 8
#define PI 3.14159265359

/*========================================================================
  Color definitions
  ========================================================================*/
#define WALL_COLOR 0x000000  // black for walls (map value 1)
#define FLOOR_COLOR 0xFFFFFF // white for floors (map value 0)
#define GRID_COLOR 0x888888  // gray grid lines

/*========================================================================
  Main game data structure
  - mlx, win: MiniLibX context and window
  - map: 8×8 grid of 0 (floor) / 1 (wall)
  - x, y: top-left pixel of the player “dot”
  - pdx, pdy: movement step in x/y based on facing angle
  - pa: player angle in radians (0 = east, π/2 = south, etc.)
  ========================================================================*/
typedef struct s_cub_data
{
	void	*mlx;
	void	*win;
	int		map[MAP_CELL][MAP_CELL];
	int x;     // player pixel x (top-left of 10×10 dot)
	int y;     // player pixel y
	float pdx; // delta x per forward/back step
	float pdy; // delta y per forward/back step
	float pa;  // player facing angle (radians)
}			t_cub;

/*========================================================================
  draw_tile:
   - Draws one TILE_SIZE×TILE_SIZE square (either wall or floor)
   - at map‐cell coordinates (x0, y0)
  ========================================================================*/
void	draw_tile(t_cub *cub, int x0, int y0, int color)
{
	int i, j;
	for (i = 0; i < TILE_SIZE; i++)
		for (j = 0; j < TILE_SIZE; j++)
			mlx_pixel_put(cub->mlx, cub->win, x0 + j, y0 + i, color);
}

/*========================================================================
  redraw:
   - Clears the window
   - Draws entire 8×8 map (walls vs floors)
   - Overlays optional grid lines
   - (Could also draw a cell highlight here if desired)
  ========================================================================*/
static void	redraw(t_cub *d)
{
	int row, col;
	int x0, y0;
	// Clear previous frame
	mlx_clear_window(d->mlx, d->win);
	// Draw each map cell
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
	// Draw horizontal grid lines
	for (row = 0; row <= MAP_CELL; row++)
		for (col = 0; col < MAP_CELL * TILE_SIZE; col++)
			mlx_pixel_put(d->mlx, d->win, col, row * TILE_SIZE, GRID_COLOR);
	// Draw vertical grid lines
	for (col = 0; col <= MAP_CELL; col++)
		for (row = 0; row < MAP_CELL * TILE_SIZE; row++)
			mlx_pixel_put(d->mlx, d->win, col * TILE_SIZE, row, GRID_COLOR);
}

/*========================================================================
  draw_dot:
   - Draws the player as a small 10×10 red square at (cub->x, cub->y)
  ========================================================================*/
void	draw_dot(t_cub *cub)
{
	int i, j;
	for (i = 0; i < DOT_DIM; i++)
		for (j = 0; j < DOT_DIM; j++)
			mlx_pixel_put(cub->mlx, cub->win, cub->x + j, cub->y + i, 0xFF0000);
}

/*========================================================================
  draw_arrow:
   - Draws a line (arrow) from the center of the dot in the direction
		the player is facing (cub->pa)
   - Uses a simple DDA line‐drawing algorithm
  ========================================================================*/
void	draw_arrow(t_cub *cub)
{
	int		center_x;
	int		center_y;
	int		arrow_length;
	int		end_x;
	int		end_y;
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;

	// Compute dot’s center
	center_x = cub->x + DOT_DIM / 2;
	center_y = cub->y + DOT_DIM / 2;
	// Determine end point based on current angle
	arrow_length = 200;
	end_x = center_x + cos(cub->pa) * arrow_length;
	end_y = center_y + sin(cub->pa) * arrow_length;
	// DDA setup
	dx = end_x - center_x;
	dy = end_y - center_y;
	steps = fmaxf(fabsf(dx), fabsf(dy));
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = center_x;
	y = center_y;
	// Draw the arrow in blue
	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(cub->mlx, cub->win, (int)x, (int)y, 0x0000FF);
		x += x_inc;
		y += y_inc;
	}
}

/*========================================================================
  draw_line_until_wall:
   - Casts a single “ray” from (start_x, start_y) in direction angle
   - Steps one pixel at a time (dx = cos, dy = sin)
   - Stops when:
		• ray goes outside map bounds
		• ray enters a wall cell (map==1)
   - Draws each step in the given color
  ========================================================================*/
void	draw_line_until_wall(t_cub *cub, float start_x, float start_y,
		float angle, int color)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	int		map_x;
	int		map_y;

	x = start_x;
	y = start_y;
	dx = cos(angle);
	dy = sin(angle);
	while (1)
	{
		map_x = (int)x / TILE_SIZE;
		map_y = (int)y / TILE_SIZE;
		// Out of bounds?
		if (map_x < 0 || map_x >= MAP_CELL || map_y < 0 || map_y >= MAP_CELL)
			break ;
		// Hit a wall?
		if (cub->map[map_y][map_x] == 1)
			break ;
		// Draw this pixel of the ray
		mlx_pixel_put(cub->mlx, cub->win, (int)x, (int)y, color);
		// Step forward one pixel
		x += dx;
		y += dy;
	}
}

/*========================================================================
  key_hook:
   - LEFT/RIGHT rotate the player by ±0.1 rad,
		then update pdx/pdy to match the new facing direction
   - UP/DOWN move the player forward/back by (pdx,pdy),
		with simple collision checking on the 10×10 dot
   - ESC quits
   - After any change, clear + redraw:
		• map + grid
		• dot
		• ray from center
  ========================================================================*/
int	key_hook(int keycode, t_cub *cub)
{
	int	new_x;
	int	new_y;

	new_x = cub->x;
	new_y = cub->y;
	int tx1, ty1, tx2, ty2;
	if (keycode == LEFT)
	{
		// Rotate left
		cub->pa -= 0.1f;
		if (cub->pa < 0)
			cub->pa += 2 * PI;
		// Update movement vector
		cub->pdx = cos(cub->pa) * DOT_SIZE;
		cub->pdy = sin(cub->pa) * DOT_SIZE;
	}
	else if (keycode == RIGHT)
	{
		// Rotate right
		cub->pa += 0.1f;
		if (cub->pa > 2 * PI)
			cub->pa -= 2 * PI;
		cub->pdx = cos(cub->pa) * DOT_SIZE;
		cub->pdy = sin(cub->pa) * DOT_SIZE;
	}
	else if (keycode == UP)
	{
		// Move forward
		new_x += (int)cub->pdx;
		new_y += (int)cub->pdy;
	}
	else if (keycode == DOWN)
	{
		// Move backward
		new_x -= (int)cub->pdx;
		new_y -= (int)cub->pdy;
	}
	else if (keycode == ESC)
	{
		exit(0);
	}
	// If we pressed UP or DOWN, perform collision check:
	if (keycode == UP || keycode == DOWN)
	{
		tx1 = new_x / TILE_SIZE;
		tx2 = (new_x + DOT_DIM - 1) / TILE_SIZE;
		ty1 = new_y / TILE_SIZE;
		ty2 = (new_y + DOT_DIM - 1) / TILE_SIZE;
		// Ensure all four corners are within floor cells
		if (tx1 >= 0 && tx2 < MAP_CELL && ty1 >= 0 && ty2 < MAP_CELL
			&& cub->map[ty1][tx1] == 0 && cub->map[ty1][tx2] == 0
			&& cub->map[ty2][tx1] == 0 && cub->map[ty2][tx2] == 0)
		{
			cub->x = new_x;
			cub->y = new_y;
		}
	}
	// Clear & redraw everything
	mlx_clear_window(cub->mlx, cub->win);
	redraw(cub);
	draw_dot(cub);
	// Cast a ray from the dot’s center in direction pa (green)
	draw_line_until_wall(cub, cub->x + DOT_DIM / 2.0f, cub->y + DOT_DIM / 2.0f,
		cub->pa, 0x00FF00);
	return (0);
}

/*========================================================================
  set_map:
   - Copies a hard‑coded 8×8 layout into cub->map
   - 1 = wall, 0 = floor
  ========================================================================*/
void	set_map(t_cub *cub)
{
	static const int literal[MAP_CELL][MAP_CELL] = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1},
	};
	ft_memcpy(cub->map, literal, sizeof literal);
}

/*========================================================================
  main: initialize everything, draw initial scene, and enter MLX loop
  ========================================================================*/
int	main(void)
{
	t_cub	cub;

	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, MAP_CELL * TILE_SIZE, MAP_CELL
			* TILE_SIZE, "cub3D demo");
	// Start the dot near the center (adjust to a floor tile for a real map)
	cub.x = WIN_WIDTH / 2;
	cub.y = WIN_HEIGHT / 2;
	cub.pa = 0.0f;                    // facing east
	cub.pdx = cos(cub.pa) * DOT_SIZE; // forward step x
	cub.pdy = sin(cub.pa) * DOT_SIZE; // forward step y
	set_map(&cub);                    // load the 8×8 map layout
	redraw(&cub);                     // draw map + grid
	draw_dot(&cub);                   // draw the player dot
	// draw initial ray for debug/visualization
	draw_line_until_wall(&cub, cub.x + DOT_DIM / 2.0f, cub.y + DOT_DIM / 2.0f,
		cub.pa, 0x00FF00);
	// Register key handler
	mlx_key_hook(cub.win, key_hook, &cub);
	// Enter the MLX loop
	mlx_loop(cub.mlx);
	return (0);
}
