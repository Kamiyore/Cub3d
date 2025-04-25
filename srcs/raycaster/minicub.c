
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

void	cast_rays(t_cub *cub)
{
	double	horizon_inter;
	double	varti_inter;
	int		ray_count;

	static int flag = 0; // aa
	ray_count = 0;
	cub->ray->angle = start_angle_of_view(cub);
	while (ray_count < SCREEN_WIDTH)
	{
		cub->ray->angle = normalize_angle(cub->ray->angle);
		// printf("angle: %f \n", cub->ray->angle * 180 / M_PI);
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
		// ray_count, 角度, h, v を出力
		if (flag < 1900)
		{
			printf("ray=%3d  ang=%.6f  step.y=%+.0f horiz=%.3f  vert=%.3f  pick=%s\n",
				ray_count, cub->ray->angle, (cub->ray->angle > 0
					&& cub->ray->angle < M_PI) ? (float)TILE_SIZE :
				-(float)TILE_SIZE, horizon_inter, varti_inter,
				(varti_inter < horizon_inter ? "VERT" : "HORIZ"));
			flag++;
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
	ray->is_vartical = false;
	return (ray);
}

t_player	*init_the_player(t_cub *cub)
{
	t_player	*ply;

	ply = ft_calloc(1, sizeof(t_player));
	ply->pixel_x = cub->map->player_x * TILE_SIZE + TILE_CENTER;
	ply->pixel_y = cub->map->player_y * TILE_SIZE + TILE_CENTER;
	ply->angle = (M_PI / 180) * 0;
	ply->view_radian = FIELD_OF_VIEW * (M_PI / 180);
	ply->rotation = false;
	ply->left_right = false;
	ply->up_down = false;
	return (ply);
}

// void	start_the_game(t_map *map)
// {
// 	t_cub	cub;

// 	cub.ply = init_the_player(cub);
// 	cub.ray = init_the_ray();
// 	cub->mlx.window = mlx_new_window(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
// 	// —— build the very first image ——
// 	cub.img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	cub.img_data = (int *)mlx_get_data_addr(cub.img_ptr, &cub.bpp, &cub.size_l,
// 			&cub.endian);
// 	mlx_loop_hook(cub->mlx.mlx, &game_loop, &cub);
// 	// mlx_key_hook(cub.win, &key_hook, &cub);
// }

//################################################################################################//
//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
//################################################################################################//

// t_map	*init_map(void)
// {
// 	t_map	*map;

// 	map = ft_calloc(1, sizeof(t_map));
// 	map->map2d = calloc(10, sizeof(char *));                // init the map
// 	map->map2d[0] = ft_strdup("1111111111111111111111111"); // fill the map
// 	map->map2d[1] = ft_strdup("1000000000001000000000011");
// 	map->map2d[2] = ft_strdup("1000000000000000000000001");
// 	map->map2d[3] = ft_strdup("1000000000000010001000001");
// 	map->map2d[4] = ft_strdup("10000000000000P0000100001");
// 	map->map2d[5] = ft_strdup("1000000000000000000000001");
// 	map->map2d[6] = ft_strdup("1000000000000000000000001");
// 	map->map2d[7] = ft_strdup("1000000000000000000000001");
// 	map->map2d[8] = ft_strdup("1111111111111111111111111");
// 	map->map2d[9] = NULL;
// 	map->player_y = 4;
// 	map->player_x = 14;
// 	map->width = 25;
// 	map->height = 9;
// 	return (map);
// }

// int	main(void)
// {
// 	t_map *map = init_map();
// 	start_the_game(map);
// 	return (0);
// }