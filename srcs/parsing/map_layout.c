/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:28:59 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/15 17:40:39 by knemcova         ###   ########.fr       */
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

int	find_player_pos(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
			{
				*x = j;
				*y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
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
	if (c == '1' || c == 'x')
		return (1);
	map[y][x] = 'x';
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

int	is_surrounded_by_walls(char **map)
{
	char	**copy;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!find_player_pos(map, &x, &y))
		return (0);
	copy = copy_map(map);
	if (!copy)
		return (ft_error("Memory allocation error"));
	if (!flood_fill(copy, x, y))
	{
		ft_free_split(copy);
		return (0);
	}
	ft_free_split(copy);
	return (1);
}


