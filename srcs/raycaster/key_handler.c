/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:50 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/16 16:05:53 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_up = 1;
	else if (keycode == KEY_S)
		game->key_down = 1;
	else if (keycode == KEY_A)
		game->key_left = 1;
	else if (keycode == KEY_D)
		game->key_right = 1;
	else if (keycode == ESC)
		exit_game(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_up = 0;
	else if (keycode == KEY_S)
		game->key_down = 0;
	else if (keycode == KEY_A)
		game->key_left = 0;
	else if (keycode == KEY_D)
		game->key_right = 0;
	return (0);
}
