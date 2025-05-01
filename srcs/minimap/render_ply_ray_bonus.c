/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ply_ray_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:08:27 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:08:27 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static bool	is_realmap_wall_bonus(t_cub *cub, float mini_ray_len,
		t_xy_f ray_step)
{
	t_xy_i			ray_cell;
	static t_xy_f	ray_pix;
	bool			is_wall;

	if (mini_ray_len == 0)
	{
		ray_pix.x = cub->ply->pixel_x;
		ray_pix.y = cub->ply->pixel_y;
	}
	ray_cell.x = (int)(ray_pix.x / TILE_SIZE);
	ray_cell.y = (int)(ray_pix.y / TILE_SIZE);
	if (ray_cell.x < 0 || ray_cell.x >= cub->map->width || ray_cell.y < 0
		|| ray_cell.y >= cub->map->height)
		is_wall = true;
	else if (cub->map->map2d[ray_cell.y][ray_cell.x] == '1')
		is_wall = true;
	else
		is_wall = false;
	ray_pix.x += ray_step.x;
	ray_pix.y += ray_step.y;
	return (is_wall);
}

static void	draw_player_minimap_bonus(t_cub *cub, t_xy_f current_pos)
{
	t_xy_i	center;

	if (BONUS_MODE == false)
		return ;
	center.x = (int)current_pos.x - PLAYER_SIZE / 2;
	center.y = (int)current_pos.y - PLAYER_SIZE / 2;
	draw_tile_bonus(cub, center, PLAYER_SIZE, PLAYER_COLOR);
}

void	draw_ray_minimap_bonus(t_cub *cub, double angle, double distance)
{
	t_xy_f	current_pos;
	t_xy_f	real_step;
	t_xy_f	mini_step;
	float	max_mlen;
	float	mlen;

	if (BONUS_MODE == false)
		return ;
	current_pos.x = cub->ply->pixel_x * cub->mini.scale;
	current_pos.y = cub->ply->pixel_y * cub->mini.scale;
	real_step.x = cosf(angle);
	real_step.y = sinf(angle);
	mini_step.x = real_step.x * cub->mini.scale;
	mini_step.y = real_step.y * cub->mini.scale;
	max_mlen = distance * cub->mini.scale;
	mlen = 0.0f;
	draw_player_minimap_bonus(cub, current_pos);
	while (mlen < max_mlen && !is_realmap_wall_bonus(cub, mlen, real_step))
	{
		safe_mlx_pixel_put_bonus(cub, (int)current_pos.x, (int)current_pos.y,
			RAY_COLOR);
		current_pos.x += mini_step.x;
		current_pos.y += mini_step.y;
		mlen += cub->mini.scale;
	}
}
