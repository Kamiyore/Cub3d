/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:37:49 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 18:26:21 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static ssize_t	count_newlines(int fd, int *count_line, char *last_char)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	ssize_t	i;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			if (buffer[i] == '\n')
				(*count_line)++;
			*last_char = buffer[i];
			i++;
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (bytes_read);
}

int	count_lines(const char *file)
{
	int		fd;
	int		count_line;
	char	last_char;
	ssize_t	result;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count_line = 0;
	last_char = '\0';
	result = count_newlines(fd, &count_line, &last_char);
	close(fd);
	if (result < 0)
		return (-1);
	if (last_char != '\0' && last_char != '\n')
		count_line++;
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
		return (close(fd), NULL);
	i = 0;
	line = ft_get_next_line(fd);
	while (i < lines && line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		array[i++] = line;
		line = ft_get_next_line(fd);
	}
	array[i] = NULL;
	close(fd);
	return (array);
}
