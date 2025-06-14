/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:25:52 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 18:26:24 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**extract_map_start(t_texture *texture, char **lines)
{
	int		i;
	char	*ln;

	i = 0;
	while (lines[i])
	{
		ln = skip_ws(lines[i]);
		if (*ln == '\0')
		{
			i++;
			continue ;
		}
		if (!((ft_strncmp(ln, "NO", 2) == 0 && ft_isspace(ln[2]))
				|| (ft_strncmp(ln, "SO", 2) == 0 && ft_isspace(ln[2]))
				|| (ft_strncmp(ln, "WE", 2) == 0 && ft_isspace(ln[2]))
				|| (ft_strncmp(ln, "EA", 2) == 0 && ft_isspace(ln[2]))
				|| (ft_strncmp(ln, "F", 1) == 0 && ft_isspace(ln[1]))
				|| (ft_strncmp(ln, "C", 1) == 0 && ft_isspace(ln[1]))))
			break ;
		if (parse_configuration(texture, ln))
			return (NULL);
		i++;
	}
	return (&lines[i]);
}

void	print_loaded_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("[%d]: \"%s\"\n", i, map[i]);
		i++;
	}
}

static bool	read_and_extract_map(t_cub *cub, const char *filename,
		char ***lines_out, char ***map_start_out)
{
	int	line_count;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (ft_error("Invalid line count or file error.\n"));
	*lines_out = read_file(filename, line_count);
	if (!*lines_out)
		return (ft_error("Could not read file into lines.\n"));
	*map_start_out = extract_map_start(&cub->color, *lines_out);
	if (!*map_start_out)
	{
		ft_array_free(*lines_out);
		free_file_data(cub);
		return (ft_error("Error in configuration.\n"));
	}
	return (0);
}

int	parse_file(t_cub *cub, const char *filename)
{
	char	**lines;
	char	**map_start;

	if (read_and_extract_map(cub, filename, &lines, &map_start) != 0)
		return (-1);
	if (parse_map_lines(cub->map, map_start) != 0)
	{
		ft_array_free(lines);
		return (ft_error("Error in map parsing.\n"));
	}
	if (validate_config_and_map(cub) != 0)
	{
		ft_array_free(lines);
		free_file_data(cub);
		return (-1);
	}
	print_loaded_map(cub->map->map2d);
	ft_array_free(lines);
	return (0);
}
