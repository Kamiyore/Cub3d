

#include "minicub.h"

//#################################################################################//
//#################################### HORIZONTAL #################################//
//#################################################################################//

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

//#################################################################################//
//##################################### VARTICAL ##################################//
//#################################################################################//

float	get_vartical_step_y(t_cub *cub)
{
	float	step;

	step = compute_opposite(TILE_SIZE, cub->ray->angle);
	if ((look_down(cub->ray->angle) && step < 0))
		step *= -1;
	else if (look_up(cub->ray->angle) && step > 0)
		step *= -1;
	return (step);
}

float	get_vartical_step_x(t_cub *cub)
{
	float step;

	if (look_right(cub->ray->angle))
		step = TILE_SIZE;
	else
		step = -TILE_SIZE;
	return (step);
}