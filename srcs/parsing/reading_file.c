/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:37:49 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/18 16:55:15 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_lines(const char *file)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	int		count_line;
	ssize_t	i;

	fd = open(file, O_RDONLY);
	count_line = 0;
	bytes_read = 1;
	while (!(fd < 0) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, sizeof(buffer));
		i = -1;
		while (++i < bytes_read)
		{
			if (count_line == INT_MAX && buffer[i] == '\n')
				return (-2);
			if (buffer[i] == '\n')
				count_line++;
		}
	}
	close(fd);
	if (fd < 0 || bytes_read < 0)
		return (-1);
	return (count_line);
}

char	**read_file(const char *file, int lines)
{
	int		fd;
	char	**array;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (lines + 1));
	if (!array)
	{
		close(fd);
		return (NULL);
	}
	i = 0;
	line = ft_get_next_line(fd);
	while (i < lines && line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		array[i] = line;
		i++;
		line = ft_get_next_line(fd);
	}
	array[i] = NULL;
	close(fd);
	return (array);
}

char	**extract_map_start(t_texture *config, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0' || lines[i][0] == '\n')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(lines[i], "NO ", 3) == 0 || ft_strncmp(lines[i], "SO ",
				3) == 0 || ft_strncmp(lines[i], "WE ", 3) == 0
			|| ft_strncmp(lines[i], "EA ", 3) == 0 || ft_strncmp(lines[i], "F ",
				2) == 0 || ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if (parse_configuration(config, lines[i]) != 0)
				return (NULL);
			i++;
		}
		else
			break ;
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

int	validate_config_and_map(t_file_data *file)
{
	t_texture	*tex;
	t_map		*map;

	tex = &file->color;
	map = &file->map;
	if (!tex->no_path || !tex->so_path || !tex->we_path || !tex->ea_path)
		return (ft_error("Missing texture path (NO, SO, WE, EA).\n"));
	if (tex->f_color == -1 || tex->c_color == -1)
		return (ft_error("Missing floor or ceiling color.\n"));
	if (!map->map || !map->map[0])
		return (ft_error("Map is missing or empty.\n"));
	return (true);
}

int	parse_file(t_file_data *file, const char *filename)
{
	int		line_count;
	char	**lines;
	char	**map_start;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (ft_error("Invalid line count or file error.\n"));
	lines = read_file(filename, line_count);
	if (!lines)
		return (ft_error("Could not read file into lines.\n"));
	map_start = extract_map_start(&file->color, lines);
	if (!map_start)
	{
		ft_free_split(lines);
		free_file_data(file);
		return (ft_error("Error in configuration.\n"));
	}
	if (!parse_map_lines(&file->map, map_start))
	{
		return (ft_error("Error in map parsing.\n"));
	}
	if (!validate_config_and_map(file))
	{
		ft_free_split(lines);
		free_file_data(file);
		return (false);
	}
	print_loaded_map(file->map.map);
	ft_free_split(lines);
	return (true);
}
