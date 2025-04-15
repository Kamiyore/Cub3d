/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:05:56 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/15 15:53:35 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		f_color;
	int		c_color;
	char	**map;
	// t_player player;
}			t_config;

int			ft_error(char *message);
int			parse_file(t_config *config, const char *filename);
int			parse_rgb(const char *str, int *dst);
int			ft_array_len(char **array);
void		ft_free_split(char **split);
int			parse_configuration(t_config *config, char *line);
int			parse_map_lines(t_config *config, char **lines);
int			validate_map(t_config *config);
int			is_player(char c);
int			is_surrounded_by_walls(char **map);
#endif