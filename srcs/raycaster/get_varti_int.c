
#include "minicub.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

static float	get_first_intersection_y(t_cub *cub, float first_itner_x)
{
	float	hor_dist;

	hor_dist = first_itner_x - cub->ply->pixel_x;
	return (cub->ply->pixel_x + compute_opposite(hor_dist, cub->ray->angle));
}

static float	get_first_intersection_x(t_cub *cub)
{
	if (cub->ray->angle > 3 * M_PI_2 || cub->ray->angle < M_PI_2)
		return (ceil(cub->ply->pixel_x / TILE_SIZE));
	else
		return (floor(cub->ply->pixel_x / TILE_SIZE));
}

static float	get_step_y(t_cub *cub, float inter_step_x)
{
	return (compute_opposite(inter_step_x, cub->ray->angle));
}

static float	get_step_x(t_cub *cub)
{
	if (cub->ray->angle > 3 * M_PI_2 || cub->ray->angle < M_PI_2)
		return (TILE_SIZE);
	else
		return (-TILE_SIZE);
}

float	get_vertical_intersection(t_cub *cub)
{
	t_xy next_inter_step;
	t_xy inter;
	t_xy dist_to_wall;

	next_inter_step.x = get_step_x(cub);
	next_inter_step.y = get_step_y(cub, next_inter_step.x);
	inter.x = get_first_intersection_x(cub);
	inter.y = get_first_intersection_y(cub, inter.x);
	while (!is_wall(cub, inter))
	{
		inter.x += next_inter_step.x;
		inter.y += next_inter_step.y;
	}
	dist_to_wall.x = inter.x - cub->ply->pixel_x;
	dist_to_wall.y = inter.y - cub->ply->pixel_y;
	return (compute_hypotenuse(dist_to_wall.x, dist_to_wall.y));
}