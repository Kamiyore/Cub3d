/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:37:49 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/15 16:25:51 by knemcova         ###   ########.fr       */
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

char	**extract_map_start(t_config *config, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] == '\0' || ft_isspace(lines[i][0]))
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

int	parse_file(t_config *config, const char *filename)
{
	int		line_count;
	char	**lines;
	char	**map_start;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (ft_error("Invalid line count or file error"));
	lines = read_file(filename, line_count);
	if (!lines)
		return (ft_error("Could not read file into lines"));
	map_start = extract_map_start(config, lines);
	if (map_start < 0)
		return (ft_error("Error in configuration"));
	if (!parse_map_lines(config, map_start))
		return (ft_error("Error in map parsing"));
	ft_free_split(lines);
	return (1);
}
