
#include "../../include/cub3d.h"

//##############################################################################################//
//############################## START THE GAME AND THE GAME LOOP ##############################//
//##############################################################################################//

int	mlx_game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_destroy_image(cub->mlx.mlx, cub->img_ptr);
	cub->img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->img_data = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp,
			&cub->size_l, &cub->endian);
	// 3) movement & rotation
	movement(cub);
	// 4) raycast into mlx->img_data[]
	render_minimap_bonus(cub);
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.window, cub->img_ptr, 0, 0);
	// mlx_put_image_to_window(cub->mlx.mlx cub->mlx.window, cub->mini.img_ptr,
	// 0, 0);
	// 1) redraw the minimap into its image buffer
	// 2) blit the minimap at the **left** corner
	if (BONUS_MODE == true)
		mlx_put_image_to_window(cub->mlx.mlx,
								cub->mlx.window,
								cub->mini.img_ptr,
								0, // x = 0 (left edge)
								0  // y = 0 (top)
		);
	return (0);
}

t_ray	*init_the_ray(void)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->angle = 0;
	ray->distance = 0;
	ray->is_vertical_wall = false;
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
// 	mlx_loop_hook(cub->mlx.mlx, &mlx_game_loop, &cub);
// 	// mlx_key_hook(cub.win, &key_hook, &cub);
// }
