/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:05:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/25 18:28:59 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define TILE_SIZE 64
# define FIELD_OF_VIEW 60
# define ROTATION_SPEED 0.045
# define MOVEMENT_SPEED 4
# define TILE_CENTER (TILE_SIZE / 2)

typedef struct s_texture_slice
{
	int *data;     // ukazatel na raw pixely textury
	double offset; // offset ve směru X (0.0–1.0)
	int			width;
	int			height;
}				t_texture_slice;

typedef struct s_texture
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f_color;
	int			c_color;
}				t_texture;

typedef struct s_map
{
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	char		player_dir;
	char		**map2d;
}				t_map;

typedef struct s_mlx
{
	void		*mlx;
	void		*window;
	void		*img_so;
	void		*img_we;
	void		*img_ea;
	void		*img_no;
	int			img_w;
	int			img_h;
	int			*tex_no_data;
	int			*tex_so_data;
	int			*tex_we_data;
	int			*tex_ea_data;
}				t_mlx;

typedef struct s_keyboard
{
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			key_esc;
}				t_keyboard;

// yuyu no yatsu
typedef struct s_player
{
	int			pixel_x;
	int			pixel_y;
	double		angle;
	float		view_radian;
	bool		rotation;
	bool		left_right;
	bool		up_down;

}				t_player;

typedef struct s_ray
{
	double		angle;
	double		distance;
	double		hit_x;
	double		hit_y;
	bool		is_vertical;
}				t_ray;

typedef struct s_cub
{
	void *img_ptr; // returned by mlx_new_image()
	int *img_data; // pixel buffer
	int bpp;       // bits per pixel
	int size_l;    // length of line (bytes)
	int endian;    // endianness
	t_ray		*ray;
	t_map		*map;
	t_player	*ply;
	t_texture	color;
	t_mlx		mlx;
	t_keyboard	key;
}				t_cub;

typedef struct s_xy
{
	float		x;
	float		y;
}				t_xy;

//#################################################################################//
//################################### FUNCTION ####################################//
//#################################################################################//

int				ft_error(char *message);
int				parse_file(t_cub *cub, const char *filename);
int				parse_rgb(const char *str, int *dst);
int				ft_array_len(char **array);
void			ft_free_split(char **split);
int				is_valid_rgb_format(const char *str);
int				parse_configuration(t_texture *color, char *line);
int				parse_map_lines(t_map *map, char **lines);
int				validate_map(t_cub *cub);
int				is_surrounded_by_wall(t_cub *cub);
bool			is_player(char c);
void			free_file_data(t_cub *cub);
void			load_images(t_cub *cub);
int				x_button_exit(t_cub *cub);
int				key_release(int keycode, t_cub *cub);
int				key_press(int keycode, t_cub *cub);
t_player		*init_the_player(t_cub *cub);
t_ray			*init_the_ray(void);
int				game_loop(void *param);
void			draw_floor_ceiling(t_cub *cub, int ray_count, int top_pix,
					int bot_pix);
void			safe_mlx_pixel_put(t_cub *cub, int x, int y, int argb);
t_player		*init_the_player(t_cub *cub);
#endif

float			get_horizontal_intersection(t_cub *cub);
float			get_vertical_intersection(t_cub *cub);
void			render_wall(t_cub *cub, int ray_count);
// helper
int				get_quandrant(float angle);
float			normalize_angle(float angle);
int				is_out_of_bounds(t_cub *cub, float inter_x, float inter_y);
int				is_wall(t_cub *cub, float inter_x, float inter_y);
float			compute_adjacent(float opposite, float angle);
float			compute_opposite(float adjacent, float angle);
float			compute_hypotenuse(float opposite, float adjacent);

// get step
float			get_horizontal_step_x(t_cub *cub);
float			get_horizontal_step_y(t_cub *cub);
float			get_vertical_step_y(t_cub *cub);
float			get_vertical_step_x(t_cub *cub);

// direction helper
bool			look_left(float angle);
bool			look_right(float angle);
bool			look_down(float angle);
bool			look_up(float angle);
