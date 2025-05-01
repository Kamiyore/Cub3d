/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:08:15 by oyuhi             #+#    #+#             */
/*   Updated: 2025/05/01 12:11:30 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*---------------------------------------------------------------------------*/
/* 1) Compute one‐tile size so that the whole world fits inside               */
/*    SCREEN_* * MINIMAP_SCALE                                              */
/*---------------------------------------------------------------------------*/
static int	compute_tile_size(t_cub *cub)
{
	t_xy_f	minimap_max;
	t_xy_f	realmap_max;
	float	scale_w;
	float	scale_h;
	float	minimap_scale;

	minimap_max.x = SCREEN_WIDTH * MINIMAP_SCALE;
	minimap_max.y = SCREEN_HEIGHT * MINIMAP_SCALE;
	realmap_max.x = cub->map->width * TILE_SIZE;
	realmap_max.y = cub->map->height * TILE_SIZE;
	scale_w = minimap_max.x / realmap_max.x;
	scale_h = minimap_max.y / realmap_max.y;
	minimap_scale = fmaxf(scale_w, scale_h);
	return (fmaxf(1.0f, TILE_SIZE * minimap_scale));
}

/*---------------------------------------------------------------------------*/
/* 2) Initialize the minimap image                                           */
/*---------------------------------------------------------------------------*/
void	init_minimap_bonus(t_cub *cub)
{
	if (BONUS_MODE == false)
		return ;
	cub->mini.tile_size = compute_tile_size(cub);
	cub->mini.scale = (float)cub->mini.tile_size / TILE_SIZE;
	cub->mini.width = cub->map->width * cub->mini.tile_size;
	cub->mini.height = cub->map->height * cub->mini.tile_size;
	cub->mini.img_ptr = mlx_new_image(cub->mlx.mlx, cub->mini.width,
			cub->mini.height);
	if (!cub->mini.img_ptr)
		exit_game(cub);
	cub->mini.img_data = (int *)mlx_get_data_addr(cub->mini.img_ptr,
			&cub->mini.bpp, &cub->mini.size_l, &cub->mini.endian);
	if (!cub->mini.img_data)
		exit_game(cub);
}
