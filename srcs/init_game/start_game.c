/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:52:16 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 12:25:01 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_ray	*init_the_ray(t_cub *cub)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
	{
		ft_error("Error: failed to allocate memory for ray\n");
		exit_game(cub);
	}
	ray->angle = 0;
	ray->distance = 0;
	ray->is_vertical_wall = false;
	return (ray);
}

/*
 * event = What you want to catch        (e.g. "Key Press Event")
 * mask  = What X11 should watch for     (e.g. "Enable key press detection")
 *
 * Event codes and masks for X11 hooks:
 *
 *   Event code   Name           Mask         Mask name
 *   ----------   ----           ----         -----------
 *    2           KeyPress       1L << 0      KeyPressMask
 *    3           KeyRelease     1L << 1      KeyReleaseMask
 *   17           DestroyNotify  0            (no mask)
 *
 * Bitmask values in binary:
 *   1L       = 0000 0001
 *   1L << 0  = 0000 0001
 *   1L << 1  = 0000 0010
 */
static void	game_hook(t_cub *cub)
{
	mlx_loop_hook(cub->mlx.mlx, &mlx_game_loop, cub);
	mlx_hook(cub->mlx.window, 2, 1L << 0, mlx_key_press, cub);
	mlx_hook(cub->mlx.window, 3, 1L << 1, mlx_key_release, cub);
	mlx_hook(cub->mlx.window, 17, 0, exit_game, cub);
	mlx_loop(cub->mlx.mlx);
}

void	start_game(t_cub *cub)
{
	cub->ply = init_the_player(cub);
	cub->ray = init_the_ray(cub);
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		exit_game(cub);
	load_images(cub);
	cub->mlx.window = mlx_new_window(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Cub3D");
	if (!cub->mlx.window)
		exit_game(cub);
	cub->img.img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!cub->img.img_ptr)
		exit_game(cub);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img_ptr, &cub->img.bpp,
			&cub->img.size_l, &cub->img.endian);
	if (!cub->img.data)
		exit_game(cub);
	init_minimap_bonus(cub);
	game_hook(cub);
}
