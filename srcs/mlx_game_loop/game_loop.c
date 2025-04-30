/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:08:07 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 20:58:18 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	mlx_game_loop(void *param)
{
	t_cub	*cub;

	cub = param;
	mlx_destroy_image(cub->mlx.mlx, cub->img.img_ptr);
	cub->img.img_ptr = mlx_new_image(cub->mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	cub->img.data = (int *)mlx_get_data_addr(cub->img.img_ptr, &cub->img.bpp,
			&cub->img.size_l, &cub->img.endian);
	movement(cub);
	render_minimap_bonus(cub);
	cast_rays(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.window, cub->img.img_ptr, 0,
		0);
	if (BONUS_MODE == true)
		mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.window,
			cub->mini.img_ptr, 0, 0);
	return (0);
}
