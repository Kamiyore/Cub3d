/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:12:03 by knemcova          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/27 09:29:08 by oyuhi            ###   ########.fr       */
=======
/*   Updated: 2025/04/23 10:42:33 by knemcova         ###   ########.fr       */
>>>>>>> debd40837a4cc76c5c5113dbaecfd60a72b24de3
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

void	init_file_data(t_minicube *cube)
{
	cube->data.color.f_color = -1;
	cube->data.color.c_color = -1;
	cube->data.color.no_path = NULL;
	cube->data.color.so_path = NULL;
	cube->data.color.we_path = NULL;
	cube->data.color.ea_path = NULL;
	cube->data.map.map = NULL;
	cube->data.map.width = 0;
	cube->data.map.height = 0;
	cube->data.map.player_x = -1;
	cube->data.map.player_y = -1;
	cube->data.map.player_dir = '\0';
}


void	start_game(t_minicube *cube)
{
	int x;
	int y;
	cube->mlx.mlx = mlx_init();
	if (!cube->mlx.mlx)
		exit(ft_error("mlx_init failed\n"));
	cube->mlx.window = mlx_new_window(cube->mlx.mlx, cube->data.map.width
			* TILE_SIZE, cube->data.map.height * TILE_SIZE, "cub3D map view");
	load_images(cube);
	y = 0;
	while (cube->data.map.map[y])
	{
		x = 0;
		while (cube->data.map.map[y][x])
		{
			if (cube->data.map.map[y][x] == '1')
				mlx_put_image_to_window(cube->mlx.mlx, cube->mlx.window,
					cube->mlx.img_no, x * TILE_SIZE, y * TILE_SIZE);
			else
				mlx_pixel_put(cube->mlx.mlx, cube->mlx.window, x * TILE_SIZE, y
					* TILE_SIZE, 0x000000);
			x++;
		}
		y++;
	}
	mlx_hook(cube->mlx.window, 2, 1L<<0, key_press, cube);
	mlx_hook(cube->mlx.window, 17, 0, x_button_exit, cube);
	mlx_key_hook(cube->mlx.window, key_press, cube);
	mlx_hook(cube->mlx.window, 3, 1L << 1, key_release, cube);
	mlx_loop(cube->mlx.mlx);
}

<<<<<<< HEAD
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
=======
int	main(int argc, char **argv)
{
	t_minicube	cube;

	if (argc != 2)
		return (ft_error("Usage: ./so_long name.ber\n"));
	init_file_data(&cube);
	if (!valid_file(argv[1]))
		return (ft_error("Invalid file format. Only '.ber'\n"));
	if (!parse_file(&cube, argv[1]))
		return (true);
	if (!validate_map(&cube))
		return (true);
	start_game(&cube);
	return (false);
}
>>>>>>> debd40837a4cc76c5c5113dbaecfd60a72b24de3
