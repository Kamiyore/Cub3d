/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_get_hori_inter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:39 by oyuhi             #+#    #+#             */
/*   Updated: 2025/05/01 14:28:15 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static float	get_first_intersection_y(t_cub *cub)
{
	float	inter_y;

	inter_y = floor(cub->ply->pixel_y / TILE_SIZE) * TILE_SIZE;
	if (look_down(cub->ray->angle))
		inter_y += TILE_SIZE;
	return (inter_y);
}

static float	get_first_intersection_x(t_cub *cub, float first_inter_y)
{
	float	vert_dist;

	vert_dist = first_inter_y - cub->ply->pixel_y;
	return (cub->ply->pixel_x + compute_adjacent(vert_dist, cub->ray->angle));
}

static float	inside_adjust_y(t_cub *cub)
{
	if (look_down(cub->ray->angle))
		return (1);
	else
		return (-1);
}

t_inter	get_horizontal_intersection(t_cub *cub)
{
	t_xy_f	next_inter_step;
	t_xy_f	dist_to_wall;
	t_inter	inter;

	next_inter_step.x = get_horizontal_step_x(cub);
	next_inter_step.y = get_horizontal_step_y(cub);
	inter.y = get_first_intersection_y(cub);
	inter.x = get_first_intersection_x(cub, inter.y);
	while (!is_out_of_bounds(cub, inter.x, inter.y + inside_adjust_y(cub)))
	{
		if (is_wall(cub, inter.x, inter.y + inside_adjust_y(cub)))
		{
			dist_to_wall.y = inter.y - cub->ply->pixel_y;
			dist_to_wall.x = inter.x - cub->ply->pixel_x;
			inter.len_to_wall = compute_hypotenuse(dist_to_wall.x,
					dist_to_wall.y);
			return (inter);
		}
		inter.y += next_inter_step.y;
		inter.x += next_inter_step.x;
	}
	inter.len_to_wall = DBL_MAX;
	return (inter);
}
