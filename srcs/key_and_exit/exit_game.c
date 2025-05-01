/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:50 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/30 20:53:28 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	exit_game(t_cub *cub)
{
	if (BONUS_MODE == true && cub->mini.img_ptr)
		mlx_destroy_image(cub->mlx.mlx, cub->mini.img_ptr);
	if (cub->mlx.img_no)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_no);
	if (cub->mlx.img_so)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_so);
	if (cub->mlx.img_we)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_we);
	if (cub->mlx.img_ea)
		mlx_destroy_image(cub->mlx.mlx, cub->mlx.img_ea);
	if (cub->mlx.window)
		mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
	if (cub->img.img_ptr)
		mlx_destroy_image(cub->mlx.mlx, cub->img.img_ptr);
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
	free_file_data(cub);
	safe_free((void **)&cub->ply);
	safe_free((void **)&cub->ray);
	exit(0);
	return (0);
}
