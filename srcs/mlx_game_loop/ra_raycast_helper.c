/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_raycast_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:08 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:44:46 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	is_out_of_bounds(t_cub *cub, float inter_x, float inter_y)
{
	int		map_index_y;
	int		map_index_x;
	char	**map2d;

	map2d = cub->map->map2d;
	map_index_y = floorf(inter_y / TILE_SIZE);
	map_index_x = floorf(inter_x / TILE_SIZE);
	if (map_index_y < 0 || map_index_y >= cub->map->height)
		return (1);
	if (map_index_x < 0 || map_index_x >= cub->map->width)
		return (1);
	else
		return (0);
}

int	is_wall(t_cub *cub, float inter_x, float inter_y)
{
	int		map_index_y;
	int		map_index_x;
	char	**map2d;

	map2d = cub->map->map2d;
	map_index_y = floorf(inter_y / TILE_SIZE);
	map_index_x = floorf(inter_x / TILE_SIZE);
	if (cub->map->map2d[map_index_y]
		&& map_index_x <= (int)ft_strlen(map2d[map_index_y]))
		if (map2d[map_index_y][map_index_x] == '1')
			return (1);
	return (0);
}
