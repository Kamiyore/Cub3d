
#include "minicub.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

static float	get_first_intersection_x(t_cub *cub)
{
	if (cub->ray->angle < M_PI_2 || cub->ray->angle > 3 * M_PI_2)
		return (ceilf(cub->ply->pixel_x / TILE_SIZE) * TILE_SIZE);
	else
		return (floorf(cub->ply->pixel_x / TILE_SIZE) * TILE_SIZE);
}

static float	get_first_intersection_y(t_cub *cub, float first_itner_x)
{
	float	hor_dist;

	hor_dist = first_itner_x - cub->ply->pixel_x;
	return (cub->ply->pixel_y + compute_opposite(hor_dist, cub->ray->angle));
}

// static float	get_step_y(t_cub *cub, float inter_step_x)
// {
// 	return (compute_opposite(inter_step_x, cub->ray->angle));
// }

static t_xy	get_vartical_step(t_cub *cub)
{
	t_xy	inter_step;

	if (cub->ray->angle < M_PI_2 || cub->ray->angle > 3 * M_PI_2)
		inter_step.x = TILE_SIZE;
	else
		inter_step.x = -TILE_SIZE;
	inter_step.y = compute_opposite(inter_step.x, cub->ray->angle);
	return (inter_step);
}

static float	inside_adjust_x(t_cub *cub)
{
	if (cub->ray->angle < M_PI_2 || cub->ray->angle > 3 * M_PI_2)
		return (0.0001f);
	else
		return (-0.0001f);
}

float	get_vertical_intersection(t_cub *cub)
{
	t_xy	next_inter_step;
	float	inter_x;
	float	inter_y;
	t_xy	dist_to_wall;

	next_inter_step = get_vartical_step(cub);
	// next_inter_step.y = get_step_y(cub, next_inter_step.x);
	inter_x = get_first_intersection_x(cub);
	inter_y = get_first_intersection_y(cub, inter_x);
	while (!is_wall(cub, inter_x + inside_adjust_x(cub), inter_y))
	{
		inter_x += next_inter_step.x;
		inter_y += next_inter_step.y;
	}
	dist_to_wall.x = inter_x - cub->ply->pixel_x;
	dist_to_wall.y = inter_y - cub->ply->pixel_y;
	return (compute_hypotenuse(dist_to_wall.x, dist_to_wall.y));
}
