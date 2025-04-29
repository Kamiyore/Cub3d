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
		return (1);
	else
		return (-1);
}

t_inter	get_vertical_intersection(t_cub *cub)
{
	t_xy_f	next_inter_step;
	t_xy_f	dist_to_wall;
	t_inter	inter;

	next_inter_step.x = get_vertical_step_x(cub);
	next_inter_step.y = get_vertical_step_y(cub);
	inter.x = get_first_intersection_x(cub);
	inter.y = get_first_intersection_y(cub, inter.x);
	while (!is_out_of_bounds(cub, inter.x + inside_adjust_x(cub), inter.y))
	{
		if (is_wall(cub, inter.x + inside_adjust_x(cub), inter.y))
		{
			dist_to_wall.x = inter.x - cub->ply->pixel_x;
			dist_to_wall.y = inter.y - cub->ply->pixel_y;
			inter.len_to_wall = compute_hypotenuse(dist_to_wall.x,
					dist_to_wall.y);
			return (inter);
		}
		inter.x += next_inter_step.x;
		inter.y += next_inter_step.y;
	}
	inter.len_to_wall = FLT_MAX;
	return (inter);
}
