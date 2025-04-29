
#include "../../include/cub3d.h"

// static float	get_step_y(t_cub *cub)
// {
// 	if (cub->ray->angle > 0 && cub->ray->angle < M_PI)
// 		return (TILE_SIZE);
// 	else
// 		return (-TILE_SIZE);
// }

// static float	get_step_x(t_cub *cub, float step_y)
// {
// 	return (compute_adjacent(step_y, cub->ray->angle));
// }

// #################################################################################//
// ########################## get_horizontal_intersection ##########################//
// #################################################################################//

static double	get_first_intersection_y(t_cub *cub)
{
	double	inter_y;

	inter_y = floor(cub->ply->pixel_y / TILE_SIZE) * TILE_SIZE;
	if (look_down(cub->ray->angle))
		inter_y += TILE_SIZE;
	return (inter_y);
}

static double	get_first_intersection_x(t_cub *cub, double first_inter_y)
{
	double	vert_dist;

	vert_dist = first_inter_y - cub->ply->pixel_y;
	return (cub->ply->pixel_x + compute_adjacent(vert_dist, cub->ray->angle));
}

static double	inside_adjust_y(t_cub *cub)
{
	if (look_down(cub->ray->angle))
		return (1);
	else
		return (-1);
}

t_inter	get_horizontal_intersection(t_cub *cub)
{
	t_xy_d	next_inter_step;
	t_xy_d	dist_to_wall;
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
	inter.len_to_wall = FLT_MAX;
	return (inter);
}

// int	inter_check(float angle, float *inter)
// {
// 	if (angle > 0 && angle < M_PI)
// 	{
// 		(void)inter;
// 		// *inter += TILE_SIZE;
// 		return (-1);
// 	}
// 	return (1);
// }

// float	get_horizontal_intersection(t_cub *mlx)
// {
// 	float	h_x;
// 	float	h_y;
// 	t_xy_f	step;
// 	int		pixel;
// 	float	angle;

// 	angle = mlx->ray->angle;
// 	step = get_horizontal_step(mlx);
// 	h_y = get_first_intersection_y(mlx);
// 	// h_y = floor(mlx->ply->pixel_y / TILE_SIZE) * TILE_SIZE;
// 	pixel = inter_check(mlx->ray->angle, &h_y);
// 	h_x = get_first_intersection_x(mlx, h_y);
// 	while (!is_out_of_bounds(mlx, h_x, h_y - pixel))
// 	{
// 		if (is_wall(mlx, h_x, h_y - pixel))
// 			return (compute_hypotenuse(h_x - mlx->ply->pixel_x, h_y
// 					- mlx->ply->pixel_y));
// 		h_x += step.x;
// 		h_y += step.y;
// 	}
// 	return (FLT_MAX);
// }
