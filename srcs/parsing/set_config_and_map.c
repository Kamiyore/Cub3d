/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_config_and_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:10:00 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/28 15:50:59 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_map_lines(t_map *map, char **lines)
{
	int	count;
	int	i;
	int	max_width;
	int	len;

	count = 0;
	i = 0;
	max_width = 0;
	while (lines[count])
		count++;
	map->map2d = malloc(sizeof(char *) * (count + 1));
	if (!map->map2d)
		return (false);
	while (i < count)
	{
		map->map2d[i] = ft_strdup(lines[i]);
		if (!map->map2d[i])
			return (false);
		len = ft_strlen(lines[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	map->map2d[i] = NULL;
	map->height = count;
	map->width = max_width;
	return (true);
}

int	parse_rgb(const char *str, int *dst)
{
	char			**color;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (!is_valid_rgb_format(str))
		return (1);
	color = ft_split(str, ",");
	if (!color)
		return (ft_error("Memory allocation error.\n"));
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	*dst = (0xFF << 24) // alfa = 0xFF
	| (r << 16)     // červená
	| (g << 8)      // zelená
	| (b << 0);     // modrá
	ft_array_free(color);
	return (0);
}


int	validate_texture_path(const char *path)
{
	int		fd;
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (ft_error("Texture file must have .xpm extension.\n"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_error("Texture file not found or inaccessible.\n"));
	close(fd);
	return (1);
}

// int	set_texture_path(char **dest, const char *line)
// {
// 	if (*dest)
// 		return (ft_error("Duplicate texture path\n"));
// 	*dest = ft_strdup(line);
// 	if (!*dest)
// 		return (ft_error("Memory allocation failed.\n"));
// 	if (!validate_texture_path(*dest))
// 		return (0);
// 	return (1);
// }


int	set_texture_path(char **dest, const char *line)
{
	if (*dest)
		return (ft_error("Duplicate texture path\n"));
	*dest = ft_strdup(line);
	if (!*dest)
		return (ft_error("Memory allocation failed.\n"));
	if (!validate_texture_path(*dest))
	{
		safe_free((void **)dest);
		return (0);
	}
	return (1);
}

int	parse_configuration(t_texture *color, char *line)
{
	while (*line && ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (!set_texture_path(&color->no_path, line + 3));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (!set_texture_path(&color->so_path, line + 3));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (!set_texture_path(&color->we_path, line + 3));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (!set_texture_path(&color->ea_path, line + 3));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_rgb(line + 2, &color->f_color));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_rgb(line + 2, &color->c_color));
	else if (*line == '\0')
		return (0);
	else
		return (ft_error("Unknown config element.\n"));
	return (0);
}
