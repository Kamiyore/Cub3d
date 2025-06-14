/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 10:15:35 by oyuhi             #+#    #+#             */
/*   Updated: 2025/05/01 18:28:56 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../srcs/minimap/minimap_bonus.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 64
# define FIELD_OF_VIEW 60
# define ROTATION_SPEED 0.045
# define MOVEMENT_SPEED 10
# define TILE_CENTER 32
# define DBL_MAX 1.7976931348623157e+308

# ifndef PRINT_MODE
#  define PRINT_MODE false
# endif

# ifndef BONUS_MODE
#  define BONUS_MODE true
# endif

typedef struct s_config
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				f_color;
	int				c_color;
	char			**map;
	// t_player player;
}					t_config;

int					ft_error(char *message);
int					parse_rgb(const char *str, int *dst);
int					ft_array_len(char **array);
void				ft_array_free(char **split);

typedef enum e_action
{
	NONE,
	MOVE_FORWARD,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT
}					t_action;

typedef struct s_wall
{
	double			height;
	double			bot_pix;
	double			top_pix;
	double			bot_screen;
	double			top_screen;
}					t_wall;

typedef struct s_xy
{
	float			x;
	float			y;
}					t_xy_f;

typedef struct s_xy_d
{
	double			x;
	double			y;
}					t_xy_d;

// typedef struct s_xy_i
// {
// 	int				x;
// 	int				y;
// }					t_xy_i;

typedef struct s_inter
{
	double			len_to_wall;
	float			x;
	float			y;
}					t_inter;

typedef struct s_player
{
	int				pixel_x;
	int				pixel_y;
	double			angle;
	float			view_radian;
	int				rotation;
	int				left_right;
	int				up_down;

}					t_player;

typedef struct s_ray
{
	double			angle;
	double			distance;

	double			inter_midpoint;
	bool			is_vertical_wall;

}					t_ray;

typedef struct s_map
{
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	char			player_dir;
	char			**map2d;
}					t_map;

typedef struct s_texture_data
{
	int				*data;
	double			offset;
	int				width;
	int				height;
}					t_texture_data;

typedef struct s_texture
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				f_color;
	int				c_color;
}					t_texture;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	void			*img_so;
	void			*img_we;
	void			*img_ea;
	void			*img_no;
	int				img_w;
	int				img_h;
	t_texture_data	tex_no_data;
	t_texture_data	tex_so_data;
	t_texture_data	tex_we_data;
	t_texture_data	tex_ea_data;
}					t_mlx;

typedef struct s_keyboard
{
	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;
	int				key_esc;
}					t_keyboard;

// void *img_ptr; // returned by mlx_new_image()
// 	int *img_data; // pixel buffer
// 	int bpp;       // bits per pixel
// 	int size_l;    // length of line (bytes)
// 	int endian;    // endianness
typedef struct s_mlx_img
{
	void			*img_ptr;
	int				*data;
	int				bpp;
	int				size_l;
	int				endian;
}					t_mlx_img;

typedef struct s_cub
{
	t_mlx_img		img;
	t_ray			*ray;
	t_map			*map;
	t_player		*ply;
	t_texture		color;
	t_mlx			mlx;
	t_keyboard		key;
	t_mini			mini;
}					t_cub;

/*
**  init_game
*/
void				start_game(t_cub *cub);
t_player			*init_the_player(t_cub *cub);
void				load_images(t_cub *cub);

/*
**  key_exit_free_whitespaces
*/
int					mlx_key_press(int keycode, void *param);
int					mlx_key_release(int keycode, void *param);
int					exit_game(t_cub *cub);
void				free_file_data(t_cub *cub);
int					ft_array_len(char **array);
void				safe_free(void **p);
char				*skip_ws(char *s);
char				*trim_ws(const char *s);
/*
**  mlx_game_loop
*/
int					mlx_game_loop(void *param);
// Movement
void				movement(t_cub *cub);
void				move_player(t_cub *cub, t_xy_i new_ply);
void				rotation(t_cub *cub);
void				cast_rays(t_cub *cub);
t_inter				get_vertical_intersection(t_cub *cub);
t_inter				get_horizontal_intersection(t_cub *cub);
// Step calculation
float				get_horizontal_step_x(t_cub *cub);
float				get_horizontal_step_y(t_cub *cub);
float				get_vertical_step_x(t_cub *cub);
float				get_vertical_step_y(t_cub *cub);
// Ray direction
bool				look_left(float angle);
bool				look_right(float angle);
bool				look_down(float angle);
bool				look_up(float angle);
//  Raycast helper
float				normalize_angle(float angle);
int					is_out_of_bounds(t_cub *cub, float x, float y);
int					is_wall(t_cub *cub, float x, float y);
// Raycast compute
float				compute_adjacent(float opposite, float angle);
float				compute_opposite(float adjacent, float angle);
float				compute_hypotenuse(float opposite, float adjacent);

// render wall
void				render(t_cub *cub, int ray_count);
void				render_wall(t_cub *cub, int ray_x, t_wall wall);
void				safe_mlx_pixel_put(t_cub *cub, int x, int y, int color);

/*
**  Parse_conf
*/
char				**read_file(const char *file, int lines);
int					count_lines(const char *file);
int					parse_configuration(t_texture *color, char *line);
int					ft_error(char *message);
int					parse_file(t_cub *cub, const char *filename);
int					validate_config_and_map(t_cub *cub);
/*
**  Parse_rgb
*/
int					is_valid_rgb_format(const char *str);
int					parse_rgb(const char *str, int *dst);
int					values_in_range(char **color);
int					parts_are_digits(char **color);
int					has_exact_commas(const char *s, int n);
int					has_three_parts(char **color);

/*
**  Parse_map
*/
int					parse_map_lines(t_map *map, char **lines);
bool				is_player(char c);
int					is_surrounded_by_wall(t_cub *cub);
int					validate_map(t_cub *cub);
int					flood_fill(char **map, int x, int y);

#endif