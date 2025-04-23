/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:24:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/23 10:12:14 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_images(t_minicube *cube)
{
	int	size;

	size = TILE_SIZE;
	cube->mlx.img_no = mlx_xpm_file_to_image(cube->mlx.mlx, cube->data.color.no_path, &size, &size);
	cube->mlx.img_so = mlx_xpm_file_to_image(cube->mlx.mlx, cube->data.color.so_path, &size, &size);
	cube->mlx.img_we = mlx_xpm_file_to_image(cube->mlx.mlx, cube->data.color.we_path, &size, &size);
	cube->mlx.img_ea = mlx_xpm_file_to_image(cube->mlx.mlx, cube->data.color.ea_path, &size, &size);
	if (!cube->mlx.img_no || !cube->mlx.img_so || !cube->mlx.img_we || !cube->mlx.img_ea)
	{
		ft_error("Error: failed to load one or more textures.\n");
		exit(1);
	}
}
