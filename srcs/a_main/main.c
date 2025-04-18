/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:12:03 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/18 20:07:34 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	return (false);
}

int	valid_map_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
		return (false);
	return (true);
}

void	init_file_data(t_file_data *file)
{
	file->color.f_color = -1;
	file->color.c_color = -1;
	file->color.no_path = NULL;
	file->color.so_path = NULL;
	file->color.we_path = NULL;
	file->color.ea_path = NULL;
	file->map.map = NULL;
}

void	start_game(t_file_data *file)
{
	void	*mlx;
	void	*win;
	int		y;
	int		x;

	y = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 640, 480, "cub3D map view");
	while (file->map.map[y])
	{
		x = 0;
		while (file->map.map[y][x])
		{
			if (file->map.map[y][x] == '1')
				mlx_pixel_put(mlx, win, x * 10, y * 10, 0xAABBBB);
			else
				mlx_pixel_put(mlx, win, x * 10, y * 10, 0x000000);
			x++;
		}
		y++;
	}
	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	t_file_data	file;

	if (argc != 2)
		return (ft_error("Usage: ./so_long name.ber\n"));
	init_file_data(&file);
	if (!valid_map_file(argv[1]))
		return (ft_error("Invalid file format. Only '.ber'\n"));
	if (!parse_file(&file, argv[1]))
		return (true);
	if (!validate_map(&file))
		return (true);
	start_game(&file);
	return (false);
}
