/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:06:34 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 20:57:58 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*
	// size_l is the number of bytes per scanline
	// divide by 4 because img_data is an int* (4 bytes per pixel)
*/
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
	idx = y * (cub->img.size_l / 4) + x;
	cub->img.data[idx] = color;
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

void	render(t_cub *cub, int ray_count)
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
	render_wall(cub, ray_count, wall);
	draw_floor_ceiling(cub, ray_count, wall.top_screen, wall.bot_screen);
}
