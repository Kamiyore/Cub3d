

#include "minicub.h"

//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

int	mlx_game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_destroy_image(cub->mlx, cub->img_ptr);
	cub->img_ptr = mlx_new_image(cub->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->img_data = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp,
			&cub->size_l, &cub->endian);
	// 3) movement & rotation
	movement(cub);
	// 4) raycast into mlx->img_data[]
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img_ptr, 0, 0);
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

t_player	*init_the_player(t_cub cub)
{
	t_player	*ply;

	ply = ft_calloc(1, sizeof(t_player));
	ply->pixel_x = cub.map->player_x * TILE_SIZE + TILE_CENTER;
	ply->pixel_y = cub.map->player_y * TILE_SIZE + TILE_CENTER;
	ply->angle = (M_PI / 180) * 0;
	ply->view_radian = FIELD_OF_VIEW * (M_PI / 180);
	ply->rotation = false;
	ply->left_right = false;
	ply->up_down = false;
	return (ply);
}

void	start_the_game(t_map *map)
{
	t_cub	cub;

	cub.map = map;
	cub.ply = init_the_player(cub);
	cub.ray = init_the_ray();
	cub.mlx = mlx_init();
	cub.win = mlx_new_window(cub.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	cub.img_ptr = mlx_new_image(cub.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub.img_data = (int *)mlx_get_data_addr(cub.img_ptr, &cub.bpp, &cub.size_l,
			&cub.endian);
	mlx_loop_hook(cub.mlx, &mlx_game_loop, &cub);
	mlx_hook(cub.win, KeyPress, KeyPressMask, &mlx_key_press, &cub);
	mlx_hook(cub.win, KeyRelease, KeyReleaseMask, &mlx_key_release, &cub);
	mlx_loop(cub.mlx);
}

//################################################################################################//
//############################## THE MAIN FUNCTION AND INIT THE MAP ##############################//
//################################################################################################//

t_map	*init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	map->map2d = calloc(10, sizeof(char *));                // init the map
	map->map2d[0] = ft_strdup("1111111111110111111111111"); // fill the map
	map->map2d[1] = ft_strdup("1000000000001000000000011");
	map->map2d[2] = ft_strdup("1000000000000000000000001");
	map->map2d[3] = ft_strdup("1000000000000010001000001");
	map->map2d[4] = ft_strdup("10000000000000P0000100001");
	map->map2d[5] = ft_strdup("1000000000000000000000001");
	map->map2d[6] = ft_strdup("1000000000000000000000001");
	map->map2d[7] = ft_strdup("1000000000000000000000001");
	map->map2d[8] = ft_strdup("1111111111111111111111111");
	map->map2d[9] = NULL;
	map->player_y = 4;
	map->player_x = 14;
	map->width = 25;
	map->height = 9;
	return (map);
}

int	main(void)
{
	t_map *map = init_map();
	start_the_game(map);
	return (0);
}