/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:24:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/27 14:54:18 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// void	image_pixel(t_cub *cub)
// {
// 	int	bpp;
// 	int	size_l;
// 	int	endian;

// 	bpp = 0;
// 	size_l = 0;
// 	endian = 0;
// 	cub->mlx.tex_no_data = (int *)mlx_get_data_addr(cub->mlx.img_no, &bpp,
// 			&size_l, &endian);
// 	cub->mlx.tex_so_data = (int *)mlx_get_data_addr(cub->mlx.img_so, &bpp,
// 			&size_l, &endian);
// 	cub->mlx.tex_we_data = (int *)mlx_get_data_addr(cub->mlx.img_we, &bpp,
// 			&size_l, &endian);
// 	cub->mlx.tex_ea_data = (int *)mlx_get_data_addr(cub->mlx.img_ea, &bpp,
// 			&size_l, &endian);
// }

// void	load_images(t_cub *cub)
// {
// 	int	size;

// 	size = TILE_SIZE;
// 	cub->mlx.img_no = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.no_path,
// 			&size, &size);
// 	cub->mlx.img_so = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.so_path,
// 			&size, &size);
// 	cub->mlx.img_we = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.we_path,
// 			&size, &size);
// 	cub->mlx.img_ea = mlx_xpm_file_to_image(cub->mlx.mlx, cub->color.ea_path,
// 			&size, &size);
// 	if (!cub->mlx.img_no || !cub->mlx.img_so || !cub->mlx.img_we
// 		|| !cub->mlx.img_ea)
// 	{
// 		ft_error("Error: failed to load one or more textures.\n");
// 		exit(1);
// 	}
// 	image_pixel(cub);
// }
void load_images(t_cub *cub)
{
    // int w, h, bpp, size_line, endian;
    int  bpp, size_line, endian;

    // North
    cub->mlx.img_no = mlx_xpm_file_to_image(
      cub->mlx.mlx, cub->color.no_path, &cub->mlx.tex_no_data.width, &cub->mlx.tex_no_data.height);
    if (!cub->mlx.img_no)
        ft_error("Error: failed to load NO texture\n");
    cub->mlx.tex_no_data.data = (int *)mlx_get_data_addr(
      cub->mlx.img_no, &bpp, &size_line, &endian);

    // South
    cub->mlx.img_so = mlx_xpm_file_to_image(
      cub->mlx.mlx, cub->color.so_path, &cub->mlx.tex_so_data.width, &cub->mlx.tex_so_data.height);
    if (!cub->mlx.img_so)
        ft_error("Error: failed to load SO texture\n");
    cub->mlx.tex_so_data.data = (int *)mlx_get_data_addr(
      cub->mlx.img_so, &bpp, &size_line, &endian);

    // West
    cub->mlx.img_we = mlx_xpm_file_to_image(
      cub->mlx.mlx, cub->color.we_path, &cub->mlx.tex_we_data.width, &cub->mlx.tex_we_data.height);
    if (!cub->mlx.img_we)
        ft_error("Error: failed to load WE texture\n");
    cub->mlx.tex_we_data.data = (int *)mlx_get_data_addr(
      cub->mlx.img_we, &bpp, &size_line, &endian);

    // East
    cub->mlx.img_ea = mlx_xpm_file_to_image(
      cub->mlx.mlx, cub->color.ea_path, &cub->mlx.tex_ea_data.width, &cub->mlx.tex_ea_data.height);
    if (!cub->mlx.img_ea)
        ft_error("Error: failed to load EA texture\n");
    cub->mlx.tex_ea_data.data = (int *)mlx_get_data_addr(
      cub->mlx.img_ea, &bpp, &size_line, &endian);

    // všechny textury mají stejné w×h, takže:
    // cub->mlx.img_w = w;
    // cub->mlx.img_h = h;
}
