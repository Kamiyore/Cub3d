/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:08:24 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:55:16 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_minimap_color(t_cub *cub, int x, int y)
{
	int	color;

	if (x < 0 || x >= cub->map->width || y < 0 || y >= cub->map->height)
		return (BACKGROUND_COLOR);
	if (cub->map->map2d[y][x] == '\0' || cub->map->map2d[y][x] == ' ')
		return (BACKGROUND_COLOR);
	if (cub->map->map2d[y][x] == '1')
		color = WALL_COLOR;
	else if (cub->map->map2d[y][x] == '0')
		color = FLOOR_COLOR;
	else
		color = BACKGROUND_COLOR;
	return (color);
}

static void	render_background_bonus(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->mini.height)
	{
		x = 0;
		while (x < cub->mini.width)
		{
			safe_mlx_pixel_put_bonus(cub, x, y, BACKGROUND_COLOR);
			x++;
		}
		y++;
	}
}

void	render_minimap_bonus(t_cub *cub)
{
	int		color;
	float	map_scale;
	t_xy_i	map_i;
	t_xy_i	pixel;

	if (BONUS_MODE == false)
		return ;
	render_background_bonus(cub);
	map_scale = (float)cub->mini.tile_size / TILE_SIZE;
	map_i.y = 0;
	while (map_i.y < cub->map->height)
	{
		map_i.x = 0;
		while (cub->map->map2d[map_i.y][map_i.x] != '\0')
		{
			color = get_minimap_color(cub, map_i.x, map_i.y);
			pixel.x = map_i.x * cub->mini.tile_size;
			pixel.y = map_i.y * cub->mini.tile_size;
			draw_tile_bonus(cub, pixel, cub->mini.tile_size, color);
			map_i.x++;
		}
		map_i.y++;
	}
}
