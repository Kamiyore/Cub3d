
#include "minicub.h"

//#################################################################################//
//########################## get_horizontal_intersection ##########################//
//#################################################################################//

static float	get_first_intersection_y(t_cub *cub)
{
	if (cub->ray->angle > 0 && cub->ray->angle < M_PI)
		return (ceilf(cub->ply->pixel_y / TILE_SIZE) * TILE_SIZE);
	else
		return (floorf(cub->ply->pixel_y / TILE_SIZE) * TILE_SIZE);
}
static float	get_first_intersection_x(t_cub *cub, float first_inter_y)
{
	float	vert_dist;

	vert_dist = first_inter_y - cub->ply->pixel_y;
	return (cub->ply->pixel_x + compute_adjacent(vert_dist, cub->ray->angle));
}

// static float	get_step_x(t_cub *cub, float step_y)
// {
// 	return (compute_adjacent(step_y, cub->ray->angle));
// }

// static float	get_step_y(t_cub *cub)
// {
// 	if (cub->ray->angle > 0 && cub->ray->angle < M_PI)
// 		return (TILE_SIZE);
// 	else
// 		return (-TILE_SIZE);
// }

static t_xy	get_horizontal_step(t_cub *cub)
{
	t_xy	step;

	if (cub->ray->angle > 0.0f && cub->ray->angle < M_PI)
		step.y = TILE_SIZE;
	else
		step.y = -TILE_SIZE;
	step.x = compute_adjacent(step.y, cub->ray->angle);
	return (step);
}

static float	inside_adjust_y(t_cub *cub)
{
	if (cub->ray->angle > 0.0f && cub->ray->angle < M_PI)
		return (0.0001f);
	else
		return (-0.0001f);
}

float	get_horizontal_intersection(t_cub *cub)
{
	t_xy	next_inter_step;
	float	inter_x;
	float	inter_y;
	t_xy	dist_to_wall;

	next_inter_step = get_horizontal_step(cub);
	inter_y = get_first_intersection_y(cub);
	inter_x = get_first_intersection_x(cub, inter_y);
	while (!is_wall(cub, inter_x, inter_y + inside_adjust_y(cub)))
	{
		inter_y += next_inter_step.y;
		inter_x += next_inter_step.x;
	}
	dist_to_wall.y = inter_y - cub->ply->pixel_y;
	dist_to_wall.x = inter_x - cub->ply->pixel_x;
	return (compute_hypotenuse(dist_to_wall.x, dist_to_wall.y));
}
