/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:24:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/24 18:56:43 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_images(t_cub *cub)
{
	int	size;

	size = TILE_SIZE;
	cub->mlx.img_no = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->color.no_path, &size, &size);
	cub->mlx.img_so = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->color.so_path, &size, &size);
	cub->mlx.img_we = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->color.we_path, &size, &size);
	cub->mlx.img_ea = mlx_xpm_file_to_image(cub->mlx.mlx,
			cub->color.ea_path, &size, &size);
	if (!cub->mlx.img_no || !cub->mlx.img_so || !cub->mlx.img_we
		|| !cub->mlx.img_ea)
	{
		ft_error("Error: failed to load one or more textures.\n");
		exit(1);
	}
}
