

#include "../../include/cub3d.h"

/*
 * Renders a single‐pixel dot for the player on the minimap,
 * erasing the previous pixel as needed.
//  */
// void render_minimap_bonus(t_cub *cub)
// {
//     static int prev_x = -1, prev_y = -1;
//     float      scale = (float)cub->mini.tile_size / (float)TILE_SIZE;
//     int        x     = (int)(cub->ply->pixel_x * scale);
//     int        y     = (int)(cub->ply->pixel_y * scale);
//     int        mx, my, bg_color;

//     // Erase the old pixel
//     if (prev_x >= 0)
//     {
//         mx = prev_x / cub->mini.tile_size;
//         my = prev_y / cub->mini.tile_size;
//         if (mx >= 0 && mx < cub->map->width
//          && my >= 0 && my < cub->map->height)
//         {
//             bg_color = (cub->map->map2d[my][mx] != '1')
//                      ? 0xFFFFFFFF  // floor
//                      : 0x808080FF; // wall
//             safe_mlx_pixel_put_bonus(cub, prev_x, prev_y, bg_color);
//         }
//     }

//     // Draw the new pixel
//     safe_mlx_pixel_put_bonus(cub, x, y, 0xFF0000FF);

//     // Remember for next frame
//     prev_x = x;
//     prev_y = y;
// }

static inline int	pack_bgra_bonus(int raw_rgba)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;

	r = (raw_rgba >> 24) & 0xFF;
	g = (raw_rgba >> 16) & 0xFF;
	b = (raw_rgba >> 8) & 0xFF;
	a = raw_rgba & 0xFF;
	// Image buffer expects: [ byte0=B ][ byte1=G ][ byte2=R ][ byte3=A ]
	return ((a << 24) | (r << 16) | (g << 8) | b);
}

void	safe_mlx_pixel_put_bonus(t_cub *cub, int x, int y, int color)
{
	int	idx;

	if (x < 0)
		return ;
	else if (x > cub->mini.width)
		return ;
	if (y < 0)
		return ;
	else if (y > cub->mini.height)
		return ;
	// size_l is the number of bytes per scanline
	// divide by 4 because img_data is an int* (4 bytes per pixel)
	int stride = cub->mini.size_l / sizeof(int); // pixels per row
	idx = y * stride + x;
	cub->mini.img_data[idx] = pack_bgra_bonus(color);
}

void	draw_tile(t_cub *cub, t_xy_i start, int tile_size, int color)
{
	t_xy_i	px;

	px.y = 0;
	while (px.y < tile_size)
	{
		px.x = 0;
		while (px.x < tile_size)
		{
			safe_mlx_pixel_put_bonus(cub, start.x + px.x, start.y + px.y,
				color);
			px.x++;
		}
		px.y++;
	}
}

#define NUM_RAYS 60
#define RAY_COLOR 0x00FF00

#define NUM_RAYS 60
#define RAY_COLOR 0x00FF00

#define MINI_RAY_COLOR 0x00FF00FF // your green on the minimap

void	draw_ray_minimap_bonus(t_cub *cub, double angle, double distance)
{
	float	map_scale;
	float	wx;
	float	wy;
	float	mx;
	float	my;
	t_xy_i	center;
	float	dxw;
	float	dyw;
	float	dxm;
	float	dym;
	float	max_mlen;
	float	mlen;
	int		cell_x;
	int		cell_y;
	

	if (BONUS_MODE == false)
		return ;
	// how many pixels on the minimap = world tilesize * map_scale
	map_scale = (float)cub->mini.tile_size / TILE_SIZE;
	// world‐space start (in px) and minimap‐space start
	wx = cub->ply->pixel_x;
	wy = cub->ply->pixel_y;
	mx = wx * map_scale;
	my = wy * map_scale;
	// unit‐step in world‐space
	dxw = cosf(angle);
	dyw = sinf(angle);
	// corresponding unit‐step in minimap‐space
	dxm = dxw * map_scale;
	dym = dyw * map_scale;
	// we will stop once minimap‐space ray length > this:
	max_mlen = distance * map_scale;
	mlen = 0.0f;
	center.x = (int)mx - 3;
	center.y = (int)my - 3;
	draw_tile(cub, center, 7, 0xFF0000FF);
	// step until either we hit a wall or exceed max_mlen
	while (mlen < max_mlen)
	{
		// first check world‐cell for a wall
		cell_x = (int)(wx / TILE_SIZE);
		cell_y = (int)(wy / TILE_SIZE);
		if (cell_x < 0 || cell_x >= cub->map->width || cell_y < 0
			|| cell_y >= cub->map->height
			|| cub->map->map2d[cell_y][cell_x] == '1')
			break ;
		// draw one pixel in minimap‐space
		safe_mlx_pixel_put_bonus(cub, (int)mx, (int)my, MINI_RAY_COLOR);
		// advance one step
		wx += dxw;
		wy += dyw;
		mx += dxm;
		my += dym;
		mlen += map_scale; // each minimap step is map_scale px long
	}
	// 3) draw the player as a small square on the minimap
	//    center it on (mx0,my0), with half‐size 3px
}

void	render_minimap_bonus(t_cub *cub)
{
	int		color;
	float	map_scale;

	if (BONUS_MODE == false)
		return ;
	t_xy_i map_i, pixel;
	map_scale = (float)cub->mini.tile_size / TILE_SIZE;
	// 1) draw the base map exactly as before
	map_i.y = 0;
	while (map_i.y < cub->map->height)
	{
		map_i.x = 0;
		while (map_i.x < cub->map->width)
		{
			color = (cub->map->map2d[map_i.y][map_i.x] == '1') ? 0x808080FF : 0xFFFFFFFF;
			pixel.x = map_i.x * cub->mini.tile_size;
			pixel.y = map_i.y * cub->mini.tile_size;
			draw_tile(cub, pixel, cub->mini.tile_size, color);
			map_i.x++;
		}
		map_i.y++;
	}
}
