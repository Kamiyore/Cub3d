/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:28:59 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/18 16:35:53 by knemcova         ###   ########.fr       */
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
	while (map_data->map[i])
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (is_player(map_data->map[i][j]))
			{
				map_data->player_x = j;
				map_data->player_y = i;
				map_data->player_dir = map_data->map[i][j];
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

int	flood_fill(char **map, int x, int y)
{
	int		width;
	int		height;
	char	c;

	height = 0;
	while (map[height])
		height++;
	if (y < 0 || y >= height)
		return (0);
	width = ft_strlen(map[y]);
	if (x < 0 || x >= width)
		return (0);
	c = map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		c = '0';
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '1')
		return (1);
	map[y][x] = '1';
	if (!flood_fill(map, x + 1, y))
		return (0);
	if (!flood_fill(map, x - 1, y))
		return (0);
	if (!flood_fill(map, x, y + 1))
		return (0);
	if (!flood_fill(map, x, y - 1))
		return (0);
	return (1);
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
				ft_free_split(copy);
				return (ft_error("Open area not enclosed.\n"));
			}
		}
	}
	return (1);
}

int	is_surrounded_by_wall(t_file_data *file)
{
	char	**copy;

	if (!find_player_pos(&file->map))
		return (ft_error("Player not found.\n"));
	copy = copy_map(file->map.map);
	if (!copy)
		return (ft_error("Memory allocation error.\n"));
	if (!flood_fill(copy, file->map.player_x, file->map.player_y))
	{
		ft_free_split(copy);
		return (ft_error("Player area not enclosed.\n"));
	}
	if (!check_remaining_open_areas(copy))
		return (0);
	ft_free_split(copy);
	return (1);
}
