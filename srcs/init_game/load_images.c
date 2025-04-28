/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:24:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/28 18:51:44 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_images(t_cub *cub)
{
	int	bpp;
	int	size_line;
	int	endian;

	cub->mlx.img_no = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.no_path,
			&cub->mlx.tex_no_data.width, &cub->mlx.tex_no_data.height);
	if (!cub->mlx.img_no)
		ft_error("Error: failed to load NO texture\n");
	cub->mlx.tex_no_data.data = (int *)mlx_get_data_addr(cub->mlx.img_no, &bpp,
			&size_line, &endian);
	cub->mlx.img_so = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.so_path,
			&cub->mlx.tex_so_data.width, &cub->mlx.tex_so_data.height);
	if (!cub->mlx.img_so)
		ft_error("Error: failed to load SO texture\n");
	cub->mlx.tex_so_data.data = (int *)mlx_get_data_addr(cub->mlx.img_so, &bpp,
			&size_line, &endian);
	cub->mlx.img_we = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.we_path,
			&cub->mlx.tex_we_data.width, &cub->mlx.tex_we_data.height);
	if (!cub->mlx.img_we)
		ft_error("Error: failed to load WE texture\n");
	cub->mlx.tex_we_data.data = (int *)mlx_get_data_addr(cub->mlx.img_we, &bpp,
			&size_line, &endian);
	cub->mlx.img_ea = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.ea_path,
			&cub->mlx.tex_ea_data.width, &cub->mlx.tex_ea_data.height);
	if (!cub->mlx.img_ea)
		ft_error("Error: failed to load EA texture\n");
	cub->mlx.tex_ea_data.data = (int *)mlx_get_data_addr(cub->mlx.img_ea, &bpp,
			&size_line, &endian);
}
