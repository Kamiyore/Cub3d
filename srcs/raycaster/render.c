
#include "../../include/cub3d.h"

/*
	// cos(θ) = adjacent (x) / hypotenuse, so x = hypotenuse * cos(θ)
	// Calculate x_step (adjacent) by multiplying hypotenuse by cos(θ).
*/
float	fix_fisheye(t_cub *cub)
{
	float	hypotenuse;
	float	angle;

	hypotenuse = cub->ray->distance;
	angle = normalize_angle(cub->ray->angle - cub->ply->angle);
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

// static void	*get_wall_image(t_cub *cub)
// {
// 	if (cub->ray->is_vertical)
// 		return (cub->ray->angle < M_PI_2 || cub->ray->angle > 3
// 			* M_PI_2) ? cub->mlx.img_ea // EAST
// 																			: cub->mlx.img_we;
// 	//  WEST
// 	else
// 		return (cub->ray->angle > 0.0f
// 			&& cub->ray->angle < M_PI) ? cub->mlx.img_so // SOUTH
// 																	: cub->mlx.img_no;
// 	//  NORTH
// }

static t_texture_slice	choose_texture_slice(t_cub *cub)
{
	t_texture_slice	slice;
	int				tile;

	tile = TILE_SIZE;
	if (cub->ray->is_vertical)
	{
		slice.data = (cub->ray->angle < M_PI_2 || cub->ray->angle > 3
				* M_PI_2) ? cub->mlx.tex_ea_data : cub->mlx.tex_we_data;
		slice.offset = fmod(cub->ray->hit_y, tile) / (double)tile;
	}
	else
	{
		slice.data = (cub->ray->angle > 0
				&& cub->ray->angle < M_PI) ? cub->mlx.tex_so_data : cub->mlx.tex_no_data;
		slice.offset = fmod(cub->ray->hit_x, tile) / (double)tile;
	}
	return (slice);
}

void	draw_wall(t_cub *cub, int ray_x, int top, int bottom)
{
	t_texture_slice	sl;
	int				tex_w;
	int				tex_h;
	double			wall_h;
	int				tex_x;
	int				color;

	sl = choose_texture_slice(cub);
	tex_w = cub->mlx.img_w;
	tex_h = cub->mlx.img_h;
	wall_h = bottom - top;
	tex_x = (int)(sl.offset * tex_w);
	for (int y = top; y < bottom; y++)
	{
		double rel = (y - top) / wall_h; // 0..1
		int tex_y = (int)(rel * tex_h);  // 0..tex_h-1
		color = sl.data[tex_y * tex_w + tex_x];
		safe_mlx_pixel_put(cub, ray_x, y, color);
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
