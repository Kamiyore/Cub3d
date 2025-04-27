
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

// static inline int	pack_bgra(int raw_rgba)
// {
// 	unsigned char	r;
// 	unsigned char	g;
// 	unsigned char	b;
// 	unsigned char	a;

// 	r = (raw_rgba >> 24) & 0xFF;
// 	g = (raw_rgba >> 16) & 0xFF;
// 	b = (raw_rgba >> 8) & 0xFF;
// 	a = raw_rgba & 0xFF;
// 	// Image buffer expects: [ byte0=B ][ byte1=G ][ byte2=R ][ byte3=A ]
// 	return ((a << 24) | (r << 16) | (g << 8) | b);
// }

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
	cub->img_data[idx] = color;
}

void	draw_floor_ceiling(t_cub *cub, int ray_count, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	while (i < SCREEN_HEIGHT)
	{
		safe_mlx_pixel_put(cub, ray_count, i, cub->color.f_color);
		i++;
	}
	i = 0;
	while (i < top_pix)
	{
		safe_mlx_pixel_put(cub, ray_count, i, cub->color.c_color);
		i++;
	}
}

t_texture_data	get_texture_data(t_cub *cub)
{
	if (cub->ray->is_vertical_wall)
	{
		if (look_right(cub->ray->angle))
			return (cub->mlx.tex_ea_data);
		else
			return (cub->mlx.tex_we_data);
	}
	else
	{
		if (look_down(cub->ray->angle))
			return (cub->mlx.tex_so_data);
		else
			return (cub->mlx.tex_no_data);
	}
}

/**
 * Compute which column of the texture to sample based on where
 * the ray hit within a TILE_SIZE‐wide wall tile.
 */
double	get_texture_x(t_cub *cub, t_texture_data sl)
{
	double	hit;

	hit = fmod(cub->ray->inter_midpoint, TILE_SIZE);
	return (hit * ((double)sl.width / TILE_SIZE));
}
/**
 * calculate_texture_start_row()
 * -----------------------------
 * Given a wall slice whose top may be above the screen, compute the
 * starting Y offset within the wall texture so sampling lines up
 * with the visible portion.
 *
 * real_top               = theoretical wall‐slice top Y (can be <0)
 * screen_top             = clamped draw start Y on screen (≥0)
 * wall_height            = wall slice height in screen pixels
 * tex_to_screen_ratio    = texture_height / wall_height
 *
 * returns: first texture row to sample (≥0)
 */
double	calculate_texture_start_row(t_wall wall, double tex_to_screen_ratio)
{
	double	skipped_rows;
	double	tex_y_start;
	double	real_top;
	double	screen_top;
	double	wall_height;

	real_top = wall.top_pix;
	screen_top = wall.top_screen;
	wall_height = wall.height;
	skipped_rows = screen_top - real_top;
	tex_y_start = skipped_rows * tex_to_screen_ratio;
	return (tex_y_start);
}

static int	get_color_from_texture(t_cub *cub, t_texture_data tx, int tex_y)
{
	int	color;
	int	tex_x;

	tex_x = get_texture_x(cub, tx);
	color = tx.data[tex_y * tx.width + tex_x];
	return (color);
}

void	draw_wall(t_cub *cub, int ray_x, t_wall wall)
{
	t_texture_data	tx;
	double			tx_step_y;
	double			tex_y;
	int				color;
	int				y;

	y = wall.top_screen;
	tx = get_texture_data(cub);
	tx_step_y = (double)tx.height / wall.height;
	tex_y = calculate_texture_start_row(wall, tx_step_y);
	while (y < wall.bot_screen)
	{
		// if ((int)tex_y > (int)tx.height)
		// {
		// 	tex_y = tx.height - 1;
		// 	printf("ty = %f tx.height = %d \n", tex_y, tx.height);
		// }
		color = get_color_from_texture(cub, tx, tex_y);
		safe_mlx_pixel_put(cub, ray_x, y, color);
		tex_y += tx_step_y;
		y++;
	}
}

void	render_wall(t_cub *cub, int ray_count)
{
	t_wall	wall;

	cub->ray->distance = fix_fisheye(cub);
	wall.height = compute_wall_height(cub);
	wall.bot_pix = (SCREEN_HEIGHT / 2) + (wall.height / 2);
	wall.top_pix = (SCREEN_HEIGHT / 2) - (wall.height / 2);
	if (wall.bot_pix > SCREEN_HEIGHT)
		wall.bot_screen = SCREEN_HEIGHT;
	else
		wall.bot_screen = wall.bot_pix;
	if (wall.top_pix < 0)
		wall.top_screen = 0;
	else
		wall.top_screen = wall.top_pix;
	draw_wall(cub, ray_count, wall);
	draw_floor_ceiling(cub, ray_count, wall.top_screen, wall.bot_screen);
}
