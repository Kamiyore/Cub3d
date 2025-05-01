/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:09:55 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 12:45:22 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_symbol(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	scan_map(t_cub *cub, int *player_cnt)
{
	int		y;
	int		x;
	char	**map;

	map = cub->map->map2d;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (!is_valid_symbol(map[y][x]))
				return (ft_error("Invalid symbol inside the map.\n"));
			if (is_player(map[y][x]))
			{
				cub->map->player_x = x;
				cub->map->player_y = y;
				cub->map->player_dir = map[y][x];
				(*player_cnt)++;
			}
		}
	}
	return (0);
}

int	validate_map(t_cub *cub)
{
	int	player_cnt;

	player_cnt = 0;
	if (scan_map(cub, &player_cnt))
		return (1);
	if (player_cnt != 1)
		return (ft_error("Map must contain exactly one player.\n"));
	return (is_surrounded_by_wall(cub));
}

int	validate_config_and_map(t_cub *cub)
{
	t_texture	*tex;
	t_map		*map;

	tex = &cub->color;
	map = cub->map;
	if (!tex->no_path || !tex->so_path || !tex->we_path || !tex->ea_path)
		return (ft_error("Missing texture path (NO, SO, WE, EA).\n"));
	if (tex->f_color == -1 || tex->c_color == -1)
		return (ft_error("Missing floor or ceiling color.\n"));
	if (!map->map2d || !map->map2d[0])
		return (ft_error("Map is missing or empty.\n"));
	return (0);
}
