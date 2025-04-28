

#include "../../include/cub3d.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

#define PRINT_MODE false

static void	print_first_raycast(t_cub *cub, int ray_count, double horizon_inter,
		double verti_inter)
{
	static int	flag = 0;

	if (PRINT_MODE == false)
		return ;
	else if (flag < 1900)
	{
		printf("ray=%3d  ang=%.3f  step.y=%+.0f horiz=%.3f  vert=%.3f  pick=%s\n",
			ray_count, cub->ray->angle, (cub->ray->angle > 0
				&& cub->ray->angle < M_PI) ? (float)TILE_SIZE :
			-(float)TILE_SIZE, horizon_inter, verti_inter,
			(verti_inter < horizon_inter ? "VERT" : "HORIZ"));
		flag++;
	}
}

static double	start_angle_of_view(t_cub *cub)
{
	double	start_angle;

	start_angle = cub->ply->angle - (cub->ply->view_radian / 2);
	return (start_angle);
}

static void	asign_shorter_inter(t_cub *cub, t_inter veri_inter,
		t_inter hori_inter)
{
	if (veri_inter.len_to_wall < hori_inter.len_to_wall)
	{
		cub->ray->distance = veri_inter.len_to_wall;
		cub->ray->inter_midpoint = veri_inter.y;
		cub->ray->is_vertical_wall = true;
	}
	else
	{
		cub->ray->distance = hori_inter.len_to_wall;
		cub->ray->inter_midpoint = hori_inter.x;
		cub->ray->is_vertical_wall = false;
	}
}

void	cast_rays(t_cub *cub)
{
	t_inter	hori_inter;
	t_inter	veri_inter;
	int		ray_count;

	ray_count = 0;
	cub->ray->angle = start_angle_of_view(cub);
	while (ray_count < SCREEN_WIDTH)
	{
		cub->ray->angle = normalize_angle(cub->ray->angle);
		veri_inter = get_vertical_intersection(cub);
		hori_inter = get_horizontal_intersection(cub);
		asign_shorter_inter(cub, veri_inter, hori_inter);
		draw_ray_minimap_bonus(cub, cub->ray->angle, cub->ray->distance);
		print_first_raycast(cub, ray_count, hori_inter.len_to_wall,
			veri_inter.len_to_wall);
		render(cub, ray_count);
		ray_count++;
		cub->ray->angle += (cub->ply->view_radian / SCREEN_WIDTH);
	}
}


