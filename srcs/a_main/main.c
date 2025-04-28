/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:01:50 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/28 16:06:43 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	return (false);
}

int	valid_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
		return (false);
	return (true);
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

// int	main(int argc, char **argv)
// {
// 	t_config	config;

// 	if (argc != 2)
// 		return (ft_error("Usage: ./so_long name.ber"));
// 	if (!valid_map_file(argv[1]))
// 		return (ft_error("Invalid file format. Only '.ber'"));
// 	if (!parse_file(&config, argv[1]))
// 		return (1);
// 	return (0);
// }

void	print_colors(t_cub *cub)
{
	int	f_r;
	int	f_g;
	int	f_b;
	int	c_r;
	int	c_g;
	int	c_b;

	f_r = (cub->color.f_color >> 16) & 0xFF;
	f_g = (cub->color.f_color >> 8) & 0xFF;
	f_b = cub->color.f_color & 0xFF;
	c_r = (cub->color.c_color >> 16) & 0xFF;
	c_g = (cub->color.c_color >> 8) & 0xFF;
	c_b = cub->color.c_color & 0xFF;
	printf("Floor Color (f_color):\n");
	printf("RGB: (%d, %d, %d)\n", f_r, f_g, f_b);
	printf("Hex: 0x%06X\n", cub->color.f_color);
	printf("\nCeiling Color (c_color):\n");
	printf("RGB: (%d, %d, %d)\n", c_r, c_g, c_b);
	printf("Hex: 0x%06X\n", cub->color.c_color);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		return (ft_error("Usage: ./so_long name.cub\n"));
	init_file_data(&cub);
	if (!valid_file(argv[1]))
		return (ft_error("Invalid file format. Only '.cub'\n"));
	if (!parse_file(&cub, argv[1]))
		return (true);
	if (!validate_map(&cub))
	{
		free_file_data(&cub);
		return (true);
	}
	print_colors(&cub);
	start_game(&cub);
	return (false);
}
