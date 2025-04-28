/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:04:50 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/28 17:04:36 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	exit_game(t_cub *cub)
{
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
	if (cub->mlx.mlx)
	{
		mlx_destroy_display(cub->mlx.mlx);
		free(cub->mlx.mlx);
	}
	if (cub->map->map2d)
		ft_array_free(cub->map->map2d);
	exit(0);
	return (0);
}
