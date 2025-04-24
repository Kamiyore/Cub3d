

#include "minicub.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

#define PRINT_MODE false

static void	print_first_raycast(t_cub *cub, int ray_count, double horizon_inter,
		double varti_inter)
{
	static int	flag = 0;

	if (PRINT_MODE == false)
		return ;
	else if (flag < 1900)
	{
		printf("ray=%3d  ang=%.3f  step.y=%+.0f horiz=%.3f  vert=%.3f  pick=%s\n",
			ray_count, cub->ray->angle, (cub->ray->angle > 0
				&& cub->ray->angle < M_PI) ? (float)TILE_SIZE :
			-(float)TILE_SIZE, horizon_inter, varti_inter,
			(varti_inter < horizon_inter ? "VERT" : "HORIZ"));
		flag++;
	}
}

static double	start_angle_of_view(t_cub *cub)
{
	double	start_angle;

	start_angle = cub->ply->angle - (cub->ply->view_radian / 2);
	return (start_angle);
}

void	cast_rays(t_cub *cub)
{
	double	horizon_inter;
	double	varti_inter;
	int		ray_count;

	ray_count = 0;
	cub->ray->angle = start_angle_of_view(cub);
	while (ray_count < SCREEN_WIDTH)
	{
		cub->ray->angle = normalize_angle(cub->ray->angle);
		horizon_inter = get_horizontal_intersection(cub);
		varti_inter = get_vertical_intersection(cub);
		if (varti_inter < horizon_inter)
		{
			cub->ray->distance = varti_inter;
			cub->ray->is_vartical = true;
		}
		else
		{
			cub->ray->distance = horizon_inter;
			cub->ray->is_vartical = false;
		}
		print_first_raycast(cub, ray_count, horizon_inter, varti_inter);
		render_wall(cub, ray_count);
		ray_count++;
		cub->ray->angle += (cub->ply->view_radian / SCREEN_WIDTH);
	}
}
