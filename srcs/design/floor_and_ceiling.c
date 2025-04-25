/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:03:24 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/24 11:37:13 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	safe_mlx_pixel_put(t_cub *cub, int x, int y, int argb)
{
	int	idx;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	idx = y * (cub->size_l / 4) + x;
	cub->img_data[idx] = argb;
}

void	draw_floor_ceiling(t_cub *cub, int ray_count, int top_pix, int bot_pix)
{
	int	i;

	i = bot_pix;
	while (i < SCREEN_HEIGHT)
	{
		safe_mlx_pixel_put(cub, ray_count, i, cub->color.f_color);
		i++;
	}
	i = 0;
	while (i < top_pix)
	{
		safe_mlx_pixel_put(cub, ray_count, i, cub->color.c_color);
		i++;
	}
}
