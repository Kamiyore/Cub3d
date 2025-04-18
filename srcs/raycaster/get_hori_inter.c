
#include "minicub.h"

//#################################################################################//
//########################## get_horizontal_intersection ##########################//
//#################################################################################//

static float	get_first_intersection_x(t_cub *cub, float first_inter_y)
{
	float	vert_dist;

	vert_dist = first_inter_y - cub->ply->pixel_y;
	return (cub->ply->pixel_x + compute_adjacent(vert_dist, cub->ray->angle));
}

static float	get_first_intersection_y(t_cub *cub)
{
	if (cub->ray->angle > 0 && cub->ray->angle < M_PI)
		return (ceil(cub->ply->pixel_y / TILE_SIZE) * TILE_SIZE);
	else
		return (floor(cub->ply->pixel_y / TILE_SIZE) * TILE_SIZE);
}

static float	get_step_x(t_cub *cub, float step_y)
{
	return (compute_adjacent(step_y, cub->ray->angle));
}

static float	get_step_y(t_cub *cub)
{
	if (cub->ray->angle > 0 && cub->ray->angle < M_PI)
		return (TILE_SIZE);
	else
		return (-TILE_SIZE);
}

float	get_horizontal_intersection(t_cub *cub)
{
	t_xy	next_inter_step;
	t_xy	inter;
	t_xy	dist_to_wall;

	next_inter_step.y = get_step_y(cub);
	next_inter_step.x = get_step_x(cub, next_inter_step.y);
	inter.y = get_first_intersection_y(cub);
	inter.x = get_first_intersection_x(cub, inter.x);
	while (!is_wall(cub, inter))
	{
		inter.y += next_inter_step.y;
		inter.x += next_inter_step.x;
	}
	dist_to_wall.y = inter.y - cub->ply->pixel_y;
	dist_to_wall.x = inter.x - cub->ply->pixel_x;
	return (compute_hypotenuse(dist_to_wall.x, dist_to_wall.y));
}
