/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:32:05 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/30 20:18:06 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_player_position(t_player *ply, t_map *map)
{
	ply->pixel_x = map->player_x * TILE_SIZE + TILE_CENTER;
	ply->pixel_y = map->player_y * TILE_SIZE + TILE_CENTER;
}

static void	set_player_angle(t_player *ply, char dir)
{
	if (dir == 'N')
		ply->angle = 3 * M_PI_2;
	else if (dir == 'S')
		ply->angle = M_PI_2;
	else if (dir == 'W')
		ply->angle = M_PI;
	else
		ply->angle = 0;
}

t_player	*init_the_player(t_cub *cub)
{
	t_player	*ply;

	ply = ft_calloc(1, sizeof(t_player));
	if (!ply)
	{
		ft_error("Memory allocation failed for player.\n");
		exit_game(cub);
	}
	set_player_position(ply, cub->map);
	set_player_angle(ply, cub->map->player_dir);
	ply->view_radian = FIELD_OF_VIEW * (M_PI / 180.0);
	cub->map->map2d[cub->map->player_y][cub->map->player_x] = '0';
	return (ply);
}
