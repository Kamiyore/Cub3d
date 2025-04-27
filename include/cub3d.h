/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:05:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/26 12:03:46 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../srcs/minimap/minimap_bonus.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
///////////yuhi//////////////////////
# include "../libft/libft.h"
# include "../srcs/minimap/minimap_bonus.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <float.h>
# include <math.h>

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

// render
void			safe_mlx_pixel_put(t_cub *cub, int x, int y, int color);

#endif
