/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:05:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/23 10:27:00 by knemcova         ###   ########.fr       */
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