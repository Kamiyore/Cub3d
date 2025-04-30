/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:08:20 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 20:04:00 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
// size_l is the number of bytes per scanline
// divide by 4 because img_data is an int* (4 bytes per pixel)
*/
void	safe_mlx_pixel_put_bonus(t_cub *cub, int x, int y, int color)
{
	int	idx;
	int	stride;

	if (x < 0)
		return ;
	else if (x > cub->mini.width)
		return ;
	if (y < 0)
		return ;
	else if (y > cub->mini.height)
		return ;
	stride = cub->mini.size_l / sizeof(int);
	idx = y * stride + x;
	cub->mini.img_data[idx] = color;
}

void	draw_tile_bonus(t_cub *cub, t_xy_i start, int tile_size, int color)
{
	t_xy_i	px;

	px.y = 0;
	while (px.y < tile_size)
	{
		px.x = 0;
		while (px.x < tile_size)
		{
			safe_mlx_pixel_put_bonus(cub, start.x + px.x, start.y + px.y,
				color);
			px.x++;
		}
		px.y++;
	}
}
