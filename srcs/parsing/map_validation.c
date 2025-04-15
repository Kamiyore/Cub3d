/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:09:55 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/15 16:46:11 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_valid_symbol(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map(t_config *config)
{
	int	horizontal;
	int	vertical;
	int	player_position;

	horizontal = 0;
	player_position = 0;
	while (config->map[horizontal] != NULL)
	{
		vertical = 0;
		while (config->map[horizontal][vertical] != '\0')
		{
			if (!is_valid_symbol(config->map[horizontal][vertical]))
				return (ft_error("Invalid symbol inside the map.\n"));
			if (is_player(config->map[horizontal][vertical]))
				player_position++;
			vertical++;
		}
		horizontal++;
	}
	if (player_position != 1)
		return (ft_error("More than one player inside the map.\n"));
	if (!is_surrounded_by_walls(config->map))
		return (ft_error("Map is not surrounded by the walls.\n"));
	return (true);
}
