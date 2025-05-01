/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:28:59 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 18:19:03 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**copy_map(char **map)
{
	int		i;
	char	**copy;

	i = 0;
	while (map[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	find_player_pos(t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map2d[i])
	{
		j = 0;
		while (map_data->map2d[i][j])
		{
			if (is_player(map_data->map2d[i][j]))
			{
				map_data->player_x = j;
				map_data->player_y = i;
				map_data->player_dir = map_data->map2d[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}

int	check_remaining_open_areas(char **copy)
{
	int	i;
	int	j;

	i = -1;
	while (copy[++i])
	{
		j = -1;
		while (copy[i][++j])
		{
			if (copy[i][j] == ' ')
				continue ;
			if (copy[i][j] == '0' && !flood_fill(copy, j, i))
			{
				ft_array_free(copy);
				return (ft_error("Open area not enclosed.\n"));
			}
		}
	}
	return (0);
}

int	is_surrounded_by_wall(t_cub *cub)
{
	char	**copy;

	if (find_player_pos(cub->map) != 0)
		return (ft_error("Player not found.\n"));
	copy = copy_map(cub->map->map2d);
	if (!copy)
		return (ft_error("Memory allocation error.\n"));
	if (!flood_fill(copy, cub->map->player_x, cub->map->player_y))
	{
		ft_array_free(copy);
		return (ft_error("Player area not enclosed.\n"));
	}
	if (check_remaining_open_areas(copy) != 0)
		return (-1);
	ft_array_free(copy);
	return (0);
}
