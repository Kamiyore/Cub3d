/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:52:16 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/30 20:51:43 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_ray	*init_the_ray(void)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	ray->angle = 0;
	ray->distance = 0;
	ray->is_vertical_wall = false;
	return (ray);
}

void	start_game(t_cub *cub)
{
	cub->mlx.img_no = NULL;
	cub->mlx.img_so = NULL;
	cub->mlx.img_we = NULL;
	cub->mlx.img_ea = NULL;
	cub->mlx.window = NULL;
	cub->img_ptr = NULL;
	cub->ply = init_the_player(cub);
	cub->ray = init_the_ray();
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		exit(ft_error("mlx_init failed.\n"));
	load_images(cub);
	cub->mlx.window = mlx_new_window(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	cub->img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->img_data = (int *)mlx_get_data_addr(cub->img_ptr, &cub->bpp,
			&cub->size_l, &cub->endian);
	init_minimap_bonus(cub);
	mlx_loop_hook(cub->mlx.mlx, &mlx_game_loop, cub);
	mlx_hook(cub->mlx.window, 2, 1L << 0, mlx_key_press, cub);
	mlx_hook(cub->mlx.window, 3, 1L << 1, mlx_key_release, cub);
	mlx_hook(cub->mlx.window, 17, 0, exit_game, cub);
	mlx_loop(cub->mlx.mlx);
}
