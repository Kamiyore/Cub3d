
#include "../../include/cub3d.h"

//#################################################################################//
//############################## THE RAYCASTING CODE ##############################//
//#################################################################################//

double	start_angle_of_view(t_cub *cub)
{
	double	start_angle;

	start_angle = cub->ply->angle - (cub->ply->view_radian / 2);
	return (start_angle);
}

// void	cast_rays(t_cub *cub)
// {
// 	double	horizon_inter;
// 	double	varti_inter;
// 	int		ray_count;

// 	static int flag = 0; // aa
// 	ray_count = 0;
// 	cub->ray->angle = start_angle_of_view(cub);
// 	while (ray_count < SCREEN_WIDTH)
// 	{
// 		cub->ray->angle = normalize_angle(cub->ray->angle);
// 		// printf("angle: %f \n", cub->ray->angle * 180 / M_PI);
// 		horizon_inter = get_horizontal_intersection(cub);
// 		varti_inter = get_vertical_intersection(cub);
// 		if (varti_inter < horizon_inter)
// 		{
// 			cub->ray->distance = varti_inter;
// 			cub->ray->is_vertical = true;
// 		}
// 		else
// 		{
// 			cub->ray->distance = horizon_inter;
// 			cub->ray->is_vertical = false;
// 		}
// 		// ray_count, 角度, h, v を出力
// 		if (flag < 1900)
// 		{
// 			printf("ray=%3d  ang=%.6f  step.y=%+.0f horiz=%.3f  vert=%.3f  pick=%s\n",
// 				ray_count, cub->ray->angle, (cub->ray->angle > 0
// 					&& cub->ray->angle < M_PI) ? (float)TILE_SIZE :
// 				-(float)TILE_SIZE, horizon_inter, varti_inter,
// 				(varti_inter < horizon_inter ? "VERT" : "HORIZ"));
// 			flag++;
// 		}
// 		render_wall(cub, ray_count);
// 		ray_count++;
// 		cub->ray->angle += (cub->ply->view_radian / SCREEN_WIDTH);
// 	}
// }
void cast_rays(t_cub *cub)
{
    double h_dist, v_dist;
    double hit_hx, hit_hy, hit_vx, hit_vy;
    int    ray_count = 0;

    cub->ray->angle = start_angle_of_view(cub);
    while (ray_count < SCREEN_WIDTH)
    {
        cub->ray->angle = normalize_angle(cub->ray->angle);

        // 1) horizontální průsečík
        h_dist = get_horizontal_intersection(cub);
        hit_hx = cub->ray->hit_x;
        hit_hy = cub->ray->hit_y;

        // 2) svislý průsečík
        v_dist = get_vertical_intersection(cub);
        hit_vx = cub->ray->hit_x;
        hit_vy = cub->ray->hit_y;

        // 3) vybereme bližší a správně nastavíme hit_x/hit_y + is_vertical
        if (v_dist < h_dist)
        {
            cub->ray->distance    = v_dist;
            cub->ray->hit_x       = hit_vx;
            cub->ray->hit_y       = hit_vy;
            cub->ray->is_vertical = true;
        }
        else
        {
            cub->ray->distance    = h_dist;
            cub->ray->hit_x       = hit_hx;
            cub->ray->hit_y       = hit_hy;
            cub->ray->is_vertical = false;
        }

        render_wall(cub, ray_count);
        ray_count++;
        cub->ray->angle += (cub->ply->view_radian / SCREEN_WIDTH);
    }
}

//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

int	game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_destroy_image(cub->mlx.mlx, cub->img_ptr);
	cub->img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->img_data = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp,
			&cub->size_l, &cub->endian);
	// 3) movement & rotation
	// hook(cub, 0, 0);
	// 4) raycast into mlx->img_data[]
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.window, cub->img_ptr, 0, 0);
	return (0);
}

t_ray	*init_the_ray(void)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->angle = 0;
	ray->distance = 0;
	ray->is_vertical = false;
	return (ray);
}

// void	start_the_game(t_map *map)
// {
// 	t_cub	cub;

// 	cub.ply = init_the_player(cub);
// 	cub.ray = init_the_ray();
// 	cub->mlx.window = mlx_new_window(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
//			"Cub3D");
// 	// —— build the very first image ——
// 	cub.img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	cub.img_data = (int *)mlx_get_data_addr(cub.img_ptr, &cub.bpp, &cub.size_l,
// 			&cub.endian);
// 	mlx_loop_hook(cub->mlx.mlx, &game_loop, &cub);
// 	// mlx_key_hook(cub.win, &key_hook, &cub);
// }