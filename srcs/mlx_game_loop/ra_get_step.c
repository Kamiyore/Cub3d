/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_get_step.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:31 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:37:51 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//#########################################################################//
//################################ HORIZONTAL #############################//
//#########################################################################//

float	get_horizontal_step_x(t_cub *cub)
{
	float	step;

	step = compute_adjacent(TILE_SIZE, cub->ray->angle);
	if ((look_left(cub->ray->angle) && step > 0))
		step *= -1;
	else if (look_right(cub->ray->angle) && step < 0)
		step *= -1;
	return (step);
}

float	get_horizontal_step_y(t_cub *cub)
{
	float	step;

	if (look_down(cub->ray->angle))
		step = TILE_SIZE;
	else
		step = -TILE_SIZE;
	return (step);
}

//#########################################################################//
//################################# vertical ##############################//
//#########################################################################//

float	get_vertical_step_y(t_cub *cub)
{
	float	step;

	step = compute_opposite(TILE_SIZE, cub->ray->angle);
	if ((look_down(cub->ray->angle) && step < 0))
		step *= -1;
	else if (look_up(cub->ray->angle) && step > 0)
		step *= -1;
	return (step);
}

float	get_vertical_step_x(t_cub *cub)
{
	float	step;

	if (look_right(cub->ray->angle))
		step = TILE_SIZE;
	else
		step = -TILE_SIZE;
	return (step);
}
