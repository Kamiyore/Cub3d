/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:05:56 by knemcova          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/27 09:27:58 by oyuhi            ###   ########.fr       */
=======
/*   Updated: 2025/04/23 10:27:00 by knemcova         ###   ########.fr       */
>>>>>>> debd40837a4cc76c5c5113dbaecfd60a72b24de3
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
///////////yuhi//////////////////////
# include "../srcs/minimap/minimap_bonus.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <float.h>
# include <math.h>

<<<<<<< HEAD
typedef struct s_config
{
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f_color;
	int			c_color;
	char		**map;
	// t_player player;
}				t_config;

int				ft_error(char *message);
int				parse_file(t_config *config, const char *filename);
int				parse_rgb(const char *str, int *dst);
int				ft_array_len(char **array);
void			ft_free_split(char **split);

///////////yuhi//////////////////////

# define SCREEN_WIDTH 1900
# define SCREEN_HEIGHT 1000
# define TILE_SIZE 64
# define FIELD_OF_VIEW 60
# define ROTATION_SPEED 0.045
# define MOVEMENT_SPEED 4
# define TILE_CENTER (TILE_SIZE / 2)

# ifndef BONUS_MODE
#  define BONUS_MODE false
# endif

typedef enum e_action
{
	NONE,
	MOVE_FORWARD,
	MOVE_BACK,
	MOVE_LEFT,
	MOVE_RIGHT,
	ROTATE_LEFT,
	ROTATE_RIGHT

}				t_action;

typedef struct s_player
{
	int			pixel_x;
	int			pixel_y;
	double		angle;
	float		view_radian;
	int			rotation;
	int			left_right;
	int			up_down;

}				t_player;

typedef struct s_ray
{
	double		angle;
	double		distance;
	bool		is_vartical;
}				t_ray;

typedef struct s_map
{
	char		**map2d;
	int			player_x;
	int			player_y;
	int			width;
	int			height;
}				t_map;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	void *img_ptr; // returned by mlx_new_image()
	int *img_data; // pixel buffer
	int bpp;       // bits per pixel
	int size_l;    // length of line (bytes)
	int endian;    // endianness
	t_ray		*ray;
	t_map		*map;
	t_player	*ply;
	t_mini		mini;
}				t_cub;

typedef struct s_xy
{
	float		x;
	float		y;
}				t_xy;

typedef struct s_xy_d
{
	double		x;
	double		y;
}				t_xy_d;

typedef struct s_xy_i
{
	int			x;
	int			y;
}				t_xy_i;

//#################################################################################//
//################################### FUNCTION ####################################//
//#################################################################################//

float			get_horizontal_intersection(t_cub *cub);
float			get_vertical_intersection(t_cub *cub);
void			render_wall(t_cub *cub, int ray_count);
void			cast_rays(t_cub *cub);

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
float			get_vartical_step_y(t_cub *cub);
float			get_vartical_step_x(t_cub *cub);

// direction helper
bool			look_left(float angle);
bool			look_right(float angle);
bool			look_down(float angle);
bool			look_up(float angle);

// keypress
int				mlx_key_press(int keycode, void *param);
int				mlx_key_release(int keycode, void *param);

// movement
void			movement(t_cub *cub);
void			rotation(t_cub *cub);
void			move_player(t_cub *cub, t_xy_i new_ply);

// kiki
int				ft_error(char *message);
int				parse_file(t_config *config, const char *filename);
int				parse_rgb(const char *str, int *dst);
int				ft_array_len(char **array);
void			ft_free_split(char **split);
int				parse_configuration(t_config *config, char *line);
int				parse_map_lines(t_config *config, char **lines);
int				validate_map(t_config *config);
int				is_player(char c);
int				is_surrounded_by_walls(char **map);

// render
void			safe_mlx_pixel_put(t_cub *cub, int x, int y, int color);

#endif
=======
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define MAX_SCREEN_WIDTH 1920
# define MAX_SCREEN_HEIGHT 1080
# define TILE_SIZE 64

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
	char		**map;
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
}				t_mlx;

typedef struct s_file_data
{
	t_texture	color;
	t_map		map;

}				t_file_data;

typedef struct s_keyboard
{
	int			key_up;
	int			key_down;
	int			key_left;
	int			key_right;
	int			key_esc;
}				t_keyboard;

typedef struct s_minicube
{
	t_file_data	data;
	t_mlx		mlx;
	t_keyboard	key;
}				t_minicube;

int				ft_error(char *message);
int				parse_file(t_minicube *cube, const char *filename);
int				parse_rgb(const char *str, int *dst);
int				ft_array_len(char **array);
void			ft_free_split(char **split);
int				is_valid_rgb_format(const char *str);
int				parse_configuration(t_texture *color, char *line);
int				parse_map_lines(t_map *map, char **lines);
int				validate_map(t_minicube *cube);
int				is_surrounded_by_wall(t_minicube *cube);
bool			is_player(char c);
void			free_file_data(t_file_data *file);
void			load_images(t_minicube *cube);
int				x_button_exit(t_minicube *cube);
int				key_release(int keycode, t_minicube *cube);
int				key_press(int keycode, t_minicube *cube);
#endif
>>>>>>> debd40837a4cc76c5c5113dbaecfd60a72b24de3
