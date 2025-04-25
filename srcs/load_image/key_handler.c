/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:50 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/24 11:55:50 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	exit_game(t_cub *cub)
{
	if (cub->mlx.img_no)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_no);
	if (cub->mlx.img_so)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_so);
	if (cub->mlx.img_we)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_we);
	if (cub->mlx.img_ea)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_ea);
	if (cub->mlx.window)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
	if (cub->map->map2d)
		ft_free_split(cub->map->map2d);
	exit(0);
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->key.key_up = 1;
	else if (keycode == KEY_S)
		cub->key.key_down = 1;
	else if (keycode == KEY_A)
		cub->key.key_left = 1;
	else if (keycode == KEY_D)
		cub->key.key_right = 1;
	else if (keycode == ESC)
		exit_game(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->key.key_up = 0;
	else if (keycode == KEY_S)
		cub->key.key_down = 0;
	else if (keycode == KEY_A)
		cub->key.key_left = 0;
	else if (keycode == KEY_D)
		cub->key.key_right = 0;
	return (0);
}

int	x_button_exit(t_cub *cub)
{
	exit_game(cub);
	return (0);
}
