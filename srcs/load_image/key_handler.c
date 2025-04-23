/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:50 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/23 10:23:41 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	exit_game(t_minicube *cube)
{
	if (cube->mlx.img_no)
		mlx_destroy_image(cube->mlx.mlx, cube->mlx.img_no);
	if (cube->mlx.img_so)
		mlx_destroy_image(cube->mlx.mlx, cube->mlx.img_so);
	if (cube->mlx.img_we)
		mlx_destroy_image(cube->mlx.mlx, cube->mlx.img_we);
	if (cube->mlx.img_ea)
		mlx_destroy_image(cube->mlx.mlx, cube->mlx.img_ea);
	if (cube->mlx.window)
		mlx_destroy_window(cube->mlx.mlx, cube->mlx.window);
	if (cube->mlx.mlx)
	{
		mlx_destroy_display(cube->mlx.mlx);
		free(cube->mlx.mlx);
	}
	if (cube->data.map.map)
		ft_free_split(cube->data.map.map);
	exit(0);
}

int	key_press(int keycode, t_minicube *cube)
{
	if (keycode == KEY_W)
		cube->key.key_up = 1;
	else if (keycode == KEY_S)
		cube->key.key_down = 1;
	else if (keycode == KEY_A)
		cube->key.key_left = 1;
	else if (keycode == KEY_D)
		cube->key.key_right = 1;
	else if (keycode == ESC)
		exit_game(cube);
	return (0);
}

int	key_release(int keycode, t_minicube *cube)
{
	if (keycode == KEY_W)
		cube->key.key_up = 0;
	else if (keycode == KEY_S)
		cube->key.key_down = 0;
	else if (keycode == KEY_A)
		cube->key.key_left = 0;
	else if (keycode == KEY_D)
		cube->key.key_right = 0;
	return (0);
}

int	x_button_exit(t_minicube *cube)
{
	exit_game(cube);
	return (0);
}
