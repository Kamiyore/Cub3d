/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_config_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:10:00 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/15 13:48:16 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_map_lines(t_config *config, char **lines)
{
	int	count;
	int	i;

	count = 0;
	while (lines[count])
		count++;
	config->map = malloc(sizeof(char *) * (count + 1));
	if (!config->map)
		return (false);
	i = 0;
	while (i < count)
	{
		config->map[i] = ft_strdup(lines[i]);
		if (!config->map[i])
			return (false);
		i++;
	}
	config->map[i] = NULL;
	return (true);
}

int	parse_rgb(const char *str, int *dst)
{
	char	**color;
	int		r;
	int		g;
	int		b;

	color = ft_split(str, ",");
	if (!color || ft_array_len(color) != 3)
	{
		ft_free_split(color);
		return (1);
	}
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_free_split(color);
		return (1);
	}
	*dst = (r << 16) | (g << 8) | b;
	ft_free_split(color);
	return (0);
}

int	parse_configuration(t_config *config, char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		config->no_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		config->so_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		config->we_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		config->ea_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_rgb(line + 2, &config->f_color));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_rgb(line + 2, &config->c_color));
	else if (*line == '\0')
		return (0);
	else
		return (ft_error("Unknown config element"));
	return (0);
}
