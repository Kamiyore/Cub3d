/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:46:15 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 12:46:42 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_out_map(char **map, int x, int y)
{
	int	height;

	height = 0;
	while (map[height])
		height++;
	if (y < 0 || y >= height)
		return (-1);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (-1);
	return (0);
}

int	flood_fill(char **map, int x, int y)
{
	char	c;

	if (is_out_map(map, x, y))
		return (0);
	c = map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		c = '0';
	if (c == ' ' || c == '\0')
		return (0);
	if (c == '1')
		return (1);
	map[y][x] = '1';
	if (!flood_fill(map, x + 1, y) || !flood_fill(map, x - 1, y)
		|| !flood_fill(map, x, y + 1) || !flood_fill(map, x, y - 1))
		return (0);
	return (1);
}
