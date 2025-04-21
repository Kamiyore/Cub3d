

#include "minicub.h"

/*
	// cos(θ) = adjacent (x) / hypotenuse, so x = hypotenuse * cos(θ)
	// Calculate x_step (adjacent) by multiplying hypotenuse by cos(θ).
*/
float	fix_fisheye(t_cub *cub)
{
	float	hypotenuse;
	float	angle;

	hypotenuse = cub->ray->distance;
	angle = cub->ray->angle - cub->ply->angle;
	return (hypotenuse * cos(angle));
}

/*
 * compute_wall_height
 *
 * Computes the height (in pixels) of a vertical wall slice to draw on screen,

	* based on the player's field of view and
	* the perpendicular distance to the wall.
 *
 * Geometry Explanation:
 * ---------------------
 * Based on similar triangles (Thalès’s theorem):
 *
 *     (real wall height)           (screen wall height)
 *   ─────────────────────     =  ───────────────────────
 *   (real distance to wall)        (distance to screen)
 *
 * Which leads to:
 *
 * -screen_wall_height = (wall_height / wall_dist) * screen_projection_dist
 *
	-real_wall_dist       : perpendicular distance to the wall (ray distance)
 * -real_wall_height      : actual wall height in world units (TILE_SIZE)
 * -screen_projection_dist: distance from player to projection plane
 *                           (computed as (SCREEN_WIDTH / 2) / tan(FOV / 2))
 * -screen_wall_height    : height of the wall slice on screen in pixels
 */
double	compute_wall_height(t_cub *cub)
{
	double	real_wall_dist;
	double	real_wall_height;
	double	screen_projection_dist;
	double	screen_wall_height;

	real_wall_dist = (double)cub->ray->distance;
	real_wall_height = (double)TILE_SIZE;
	screen_projection_dist = (double)compute_adjacent((double)SCREEN_WIDTH
			/ 2.0, cub->ply->view_radian / 2.0);
	screen_wall_height = (real_wall_height / real_wall_dist)
		* screen_projection_dist;
	return (screen_wall_height);
}

static inline int	pack_bgra(int raw_rgba)
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

void	safe_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	int	idx;

	if (x < 0)
		return ;
	else if (x > SCREEN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y > SCREEN_HEIGHT)
		return ;
	// size_l is the number of bytes per scanline
	// divide by 4 because img_data is an int* (4 bytes per pixel)
	idx = y * (cub->size_l / 4) + x;
	cub->img_data[idx] = pack_bgra(color);
}

void	draw_floor_ceiling(t_cub *cub, int ray_count, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	while (i < SCREEN_HEIGHT)
	{
		safe_mlx_pixel_put(cub, ray_count, i, 0xB99470FF); // todo floor color
		i++;
	}
	i = 0;
	while (i < top_pix)
	{
		safe_mlx_pixel_put(cub, ray_count, i, 0x89CFF3FF); // todo ceiling color
		i++;
	}
}

// int	get_color(t_cub *cub)
// {
// 	float	a;

// 	a = normalize_angle(cub->ray->angle);
// if (cub->ray->is_vartical)
// {
// 	// Vertical wall: South vs North
// 	if (a > 0.0f && a < M_PI)
// 		return (0xD94C4CFF); // SOUTH → soft red
// 	else
// 		return (0x4C6ED9FF); // NORTH → soft blue
// }
// else
// {
// 	// Horizontal wall: West vs East
// 	if (a > M_PI_2 && a < 3.0f * M_PI_2)
// 		return (0xE1D66FFF); // WEST → warm yellow
// 	else
// 		return (0x6FD96FFF); // EAST → soft green
// }
// }
//↑間違ってたぽい

//↓あってそう
int	get_color(t_cub *cub)
{
	float	a;

	a = normalize_angle(cub->ray->angle);
	if (cub->ray->is_vartical)
	{
		// 垂直グリッド → 東西の壁
		if (a > M_PI_2 && a < 3.0f * M_PI_2)
			return (0x6FD96FFF); // EAST（右壁：緑）
		else
			return (0xE1D66FFF); // WEST（左壁：黄）
	}
	else
	{
		// 水平グリッド → 南北の壁
		if (a > 0.0f && a < M_PI)
			return (0xD94C4CFF); // SOUTH（下方向の壁：赤）
		else
			return (0x4C6ED9FF); // NORTH（上方向の壁：青）
	}
}

void	draw_wall(t_cub *cub, int ray_count, int top_pix, int bot_pix)
{
	int	color;

	color = get_color(cub);
	while (top_pix < bot_pix)
	{
		safe_mlx_pixel_put(cub, ray_count, top_pix, color);
		top_pix++;
	}
}

void	render_wall(t_cub *cub, int ray_count)
{
	double	wall_height;
	double	bot_pix;
	double	top_pix;

	cub->ray->distance = fix_fisheye(cub);
	wall_height = compute_wall_height(cub);
	bot_pix = (SCREEN_HEIGHT / 2) + (wall_height / 2);
	if (bot_pix > SCREEN_HEIGHT)
		bot_pix = SCREEN_HEIGHT;
	top_pix = (SCREEN_HEIGHT / 2) - (wall_height / 2);
	if (top_pix < 0)
		top_pix = 0;
	draw_wall(cub, ray_count, top_pix, bot_pix);
	draw_floor_ceiling(cub, ray_count, top_pix, bot_pix);
}
