/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:01:50 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 20:05:47 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	return (-1);
}

int	valid_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
		return (-1);
	return (0);
}

void	init_file_data(t_cub *cub)
{
	cub->map = ft_calloc(1, sizeof(t_map));
	if (!cub->map)
		exit(ft_error("Memory allocation failed for map.\n"));
	cub->color.f_color = -1;
	cub->color.c_color = -1;
	cub->color.no_path = NULL;
	cub->color.so_path = NULL;
	cub->color.we_path = NULL;
	cub->color.ea_path = NULL;
	cub->map->map2d = NULL;
	cub->map->width = 0;
	cub->map->height = 0;
	cub->map->player_x = -1;
	cub->map->player_y = -1;
	cub->map->player_dir = '\0';
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_error("Usage: ./so_long name.cub\n"));
	init_file_data(&cub);
	if (valid_file(argv[1]) != 0)
	{
		free_file_data(&cub);
		return (ft_error("Invalid file format. Only '.cub'\n"));
	}
	if (parse_file(&cub, argv[1]) != 0)
		return (true);
	if (validate_map(&cub) != 0)
	{
		free_file_data(&cub);
		return (true);
	}
	start_game(&cub);
	return (false);
}

// print_colors(&cub);