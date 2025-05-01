/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:24:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 18:39:50 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	load_texture(void *mlx_ptr, const char *path, void **img_out,
		t_texture_data *tex_out)
{
	int	bpp;
	int	size_line;
	int	endian;

	*img_out = mlx_xpm_file_to_image(mlx_ptr, (char *)path, &tex_out->width,
			&tex_out->height);
	if (!*img_out)
		return (ft_error("Error: failed to load texture\n"));
	tex_out->data = (int *)mlx_get_data_addr(*img_out, &bpp, &size_line,
			&endian);
	return (0);
}

void	load_images(t_cub *cub)
{
	if (load_texture(cub->mlx.mlx, cub->color.no_path, &cub->mlx.img_no,
			&cub->mlx.tex_no_data) || load_texture(cub->mlx.mlx,
			cub->color.so_path, &cub->mlx.img_so, &cub->mlx.tex_so_data)
		|| load_texture(cub->mlx.mlx, cub->color.we_path, &cub->mlx.img_we,
			&cub->mlx.tex_we_data) || load_texture(cub->mlx.mlx,
			cub->color.ea_path, &cub->mlx.img_ea, &cub->mlx.tex_ea_data))
		exit_game(cub);
}
