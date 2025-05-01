/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_render_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:06:39 by oyuhi             #+#    #+#             */
/*   Updated: 2025/05/01 17:27:28 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_texture_data	get_texture_data(t_cub *cub)
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
static double	get_texture_x(t_cub *cub, t_texture_data sl)
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
static double	calculate_texture_start_row(t_wall wall,
		double tex_to_screen_ratio)
{
	double	skipped_rows;
	double	tex_y_start;
	double	real_top;
	double	screen_top;

	real_top = wall.top_pix;
	screen_top = wall.top_screen;
	skipped_rows = screen_top - real_top;
	tex_y_start = skipped_rows * tex_to_screen_ratio;
	return (tex_y_start);
}

static int	get_color_from_texture(t_cub *cub, t_texture_data tx, int tex_y)
{
	int	tex_x;

	tex_x = get_texture_x(cub, tx);
	if ((cub->ray->is_vertical_wall && look_left(cub->ray->angle))
		|| (!cub->ray->is_vertical_wall && look_down(cub->ray->angle)))
	{
		tex_x = tx.width - tex_x - 1;
	}
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= tx.width)
		tex_x = tx.width - 1;
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= tx.height)
		tex_y = tx.height - 1;
	return (tx.data[tex_y * tx.width + tex_x]);
}

void	render_wall(t_cub *cub, int ray_x, t_wall wall)
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
		if ((int)tex_y > (int)tx.height)
			tex_y = tx.height - 1;
		color = get_color_from_texture(cub, tx, tex_y);
		safe_mlx_pixel_put(cub, ray_x, y, color);
		tex_y += tx_step_y;
		y++;
	}
}
