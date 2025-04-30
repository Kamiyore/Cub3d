/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_move_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:59 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:52:29 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	move_only_y(t_cub *cub, t_xy_i new_cell, t_xy_i old_cell,
		t_xy_i new_ply)
{
	char	**map2d;

	map2d = cub->map->map2d;
	if (map2d[new_cell.y][old_cell.x] == '1')
	{
		if (map2d[old_cell.y][new_cell.x] != '1')
		{
			cub->ply->pixel_x = new_ply.x;
			return (Success);
		}
	}
	return (EXIT_FAILURE);
}

static int	move_only_x(t_cub *cub, t_xy_i new_cell, t_xy_i old_cell,
		t_xy_i new_ply)
{
	char	**map2d;

	map2d = cub->map->map2d;
	if (map2d[old_cell.y][new_cell.x] == '1')
	{
		if (map2d[new_cell.y][old_cell.x] != '1')
		{
			cub->ply->pixel_y = new_ply.y;
			return (Success);
		}
	}
	return (EXIT_FAILURE);
}

static int	move_to_new_cell(t_cub *cub, t_xy_i new_cell, t_xy_i old_cell,
		t_xy_i new_ply)
{
	char	**map2d;

	map2d = cub->map->map2d;
	if (map2d[new_cell.y][new_cell.x] != '1')
	{
		if (map2d[old_cell.y][new_cell.x] != '1')
		{
			if (map2d[new_cell.y][old_cell.x] != '1')
			{
				cub->ply->pixel_x = new_ply.x;
				cub->ply->pixel_y = new_ply.y;
				return (Success);
			}
		}
	}
	return (EXIT_FAILURE);
}

static int	is_out_of_map(t_cub *cub, t_xy_i new_cell, t_xy_i old_cell)
{
	char	**map2d;

	map2d = cub->map->map2d;
	if (new_cell.x < 0 || new_cell.x >= cub->map->width)
		return (true);
	if (new_cell.y < 0 || new_cell.y >= cub->map->height)
		return (true);
	if (old_cell.x < 0 || old_cell.x >= cub->map->width)
		return (true);
	if (old_cell.y < 0 || old_cell.y >= cub->map->height)
		return (true);
	return (false);
}

void	move_player(t_cub *cub, t_xy_i new_ply)
{
	t_xy_i	new_cell;
	t_xy_i	old_cell;

	new_cell.x = floorf(new_ply.x / TILE_SIZE);
	new_cell.y = floorf(new_ply.y / TILE_SIZE);
	old_cell.x = floorf(cub->ply->pixel_x / TILE_SIZE);
	old_cell.y = floorf(cub->ply->pixel_y / TILE_SIZE);
	if (is_out_of_map(cub, new_cell, old_cell) == true)
		return ;
	else if (move_to_new_cell(cub, new_cell, old_cell, new_ply) == Success)
		return ;
	else if (move_only_x(cub, new_cell, old_cell, new_ply) == Success)
		return ;
	else if (move_only_y(cub, new_cell, old_cell, new_ply) == Success)
		return ;
}
