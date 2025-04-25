#include "../../include/cub3d.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

static float	get_first_intersection_x(t_cub *cub)
{
	float	inter_x;

	inter_x = floor(cub->ply->pixel_x / TILE_SIZE) * TILE_SIZE;
	if (look_right(cub->ray->angle))
		inter_x += TILE_SIZE;
	return (inter_x);
}

static float	get_first_intersection_y(t_cub *cub, float first_itner_x)
{
	float	hor_dist;

	hor_dist = first_itner_x - cub->ply->pixel_x;
	return (cub->ply->pixel_y + compute_opposite(hor_dist, cub->ray->angle));
}

static float	inside_adjust_x(t_cub *cub)
{
	if (look_right(cub->ray->angle))
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

	next_inter_step.x = get_vartical_step_x(cub);
	next_inter_step.y = get_vartical_step_y(cub);
	inter_x = get_first_intersection_x(cub);
	inter_y = get_first_intersection_y(cub, inter_x);
	while (!is_out_of_bounds(cub, inter_x + inside_adjust_x(cub), inter_y))
	{
		if (is_wall(cub, inter_x + inside_adjust_x(cub), inter_y))
		{
			dist_to_wall.x = inter_x - cub->ply->pixel_x;
			dist_to_wall.y = inter_y - cub->ply->pixel_y;
			return (compute_hypotenuse(dist_to_wall.x, dist_to_wall.y));
		}
		inter_x += next_inter_step.x;
		inter_y += next_inter_step.y;
	}
	return (FLT_MAX);
}
