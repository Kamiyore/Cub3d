/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:37:49 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:27 by knemcova         ###   ########.fr       */
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
		array[i] = line;
		i++;
		line = ft_get_next_line(fd);
	}
	array[i] = NULL;
	close(fd);
	return (array);
}

int	parse_rgb(const char *str, int *dst)
{
	char	**color;
	int		r;
	int		g;
	int		b;

	color = ft_split(str,",");
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

int	parse_line(t_config *config, char *line)
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

int	parse_file(t_config *config, const char *filename)
{
	int		line_count;
	char	**lines;
	int		i;

	line_count = count_lines(filename);
	if (line_count <= 0)
		return (ft_error("Invalid line count or file error"));
	lines = read_file(filename, line_count);
	if (!lines)
		return (ft_error("Could not read file into lines"));
	i = 0;
	while (lines[i])
	{
		if (parse_line(config, lines[i]) != 0)
			return (free(lines), (ft_error("Error parsing line")));
		i++;
	}
	return (1);
}
