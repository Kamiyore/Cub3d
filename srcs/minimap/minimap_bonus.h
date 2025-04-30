/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 20:03:28 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 20:03:29 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# define MINIMAP_SCALE 0.3
# define NUM_RAYS 60
# define PLAYER_SIZE 5

// Color format: ARGB → [byte0=A][byte1=R][byte2=G][byte3=B]
// Color format: BGRA (memory order on little-endian systems)
// Stored as: [byte0 = Blue] [byte1 = Green] [byte2 = Red] [byte3 = Alpha]

// [B=0x00] [G=0x00] [R=0xFF] [A=0xFF] red
# define PLAYER_COLOR 0xFFFF0000

// [B=0x00] [G=0x00] [R=0xFF] [A=0xFF] red
# define RAY_COLOR 0xFFFF0000

// [B=0x80] [G=0x80] [R=0x80] [A=0xFF] gray
# define BACKGROUND_COLOR 0xFF808080

// [B=0x00] [G=0x00] [R=0x00] [A=0xFF] black
# define WALL_COLOR 0xFF000000

// [B=0xFF] [G=0xFF] [R=0xFF] [A=0xFF] white
# define FLOOR_COLOR 0xFFFFFFFF

typedef struct s_cub	t_cub;

// void *img_ptr; // returned by mlx_new_image()
// int *img_data; // pixel buffer
// int bpp;       // bits per pixel
// int size_l;    // length of line (bytes)
// int endian;    // endianness
typedef struct s_mini
{
	void				*img_ptr;
	int					*img_data;
	int					bpp;
	int					size_l;
	int					endian;
	int					width;
	int					height;
	int					tile_size;
	float				scale;
}						t_mini;

typedef struct s_xy_i
{
	int					x;
	int					y;
}						t_xy_i;

void					render_minimap_bonus(t_cub *cub);
void					init_minimap_bonus(t_cub *cub);
void					draw_ray_minimap_bonus(t_cub *cub, double angle,
							double distance);
void					safe_mlx_pixel_put_bonus(t_cub *cub, int x, int y,
							int color);
void					draw_tile_bonus(t_cub *cub, t_xy_i start, int tile_size,
							int color);

#endif