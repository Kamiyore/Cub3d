/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_config_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:10:00 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 17:10:41 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_map_lines(t_map *map, char **lines)
{
	int	i;
	int	len;

	map->height = 0;
	while (lines[map->height])
		map->height++;
	map->map2d = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map2d)
		return (-1);
	map->width = 0;
	i = 0;
	while (i < map->height)
	{
		map->map2d[i] = ft_strdup(lines[i]);
		if (!map->map2d[i])
			return (-1);
		len = ft_strlen(lines[i]);
		if (len > map->width)
			map->width = len;
		i++;
	}
	map->map2d[i] = NULL;
	return (0);
}

int	parse_rgb(const char *str, int *dst)
{
	char			**color;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (is_valid_rgb_format(str) != 0)
		return (-1);
	color = ft_split(str, ",");
	if (!color)
		return (ft_error("Memory allocation error.\n"));
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	*dst = (0xFF << 24) | (r << 16) | (g << 8) | (b << 0);
	ft_array_free(color);
	return (0);
}

int	validate_texture_path(const char *path)
{
	int		fd;
	size_t	len;

	if (!path)
		return (-1);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (ft_error("Texture file must have .xpm extension.\n"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Texture file not found or inaccessible.\n"));
	close(fd);
	return (0);
}

int	set_texture_path(char **dst, const char *raw)
{
	char	*path;

	if (*dst)
		return (ft_error("Duplicate texture path\n"));
	path = trim_ws((char *)raw);
	if (!path)
		return (ft_error("Memory allocation failed.\n"));
	if (validate_texture_path(path) != 0)
	{
		free(path);
		return (-1);
	}
	*dst = path;
	return (0);
}

int	parse_configuration(t_texture *tex, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
		return (set_texture_path(&tex->no_path, skip_ws(line + 2)));
	if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
		return (set_texture_path(&tex->so_path, skip_ws(line + 2)));
	if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
		return (set_texture_path(&tex->we_path, skip_ws(line + 2)));
	if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
		return (set_texture_path(&tex->ea_path, skip_ws(line + 2)));
	if (ft_strncmp(line, "F", 1) == 0 && ft_isspace(line[1]))
		return (parse_rgb(skip_ws(line + 1), &tex->f_color));
	if (ft_strncmp(line, "C", 1) == 0 && ft_isspace(line[1]))
		return (parse_rgb(skip_ws(line + 1), &tex->c_color));
	if (*line == '\0')
		return (0);
	return (ft_error("Unknown config element.\n"));
}
