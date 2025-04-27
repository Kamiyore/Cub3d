
#ifndef MINIMAP_BONUS_H
# define MINIMAP_BONUS_H

# define MINIMAP_SCALE 0.3

typedef struct s_cub	t_cub;

typedef struct s_mini
{
	void *img_ptr; // returned by mlx_new_image()
	int *img_data; // pixel buffer
	int bpp;       // bits per pixel
	int size_l;    // length of line (bytes)
	int endian;    // endianness
	int					width;
	int					height;
	int					tile_size;
}						t_mini;



void					safe_mlx_pixel_put_bonus(t_cub *cub, int x, int y,
							int color);
void					render_minimap_bonus(t_cub *cub);
void					init_minimap_bonus(t_cub *cub);
void					my_mlx_pixel_put_bonus(t_cub *cub, int x, int y,
							int color);
void					draw_ray_minimap_bonus(t_cub *cub, double angle,
							double distance);

#endif