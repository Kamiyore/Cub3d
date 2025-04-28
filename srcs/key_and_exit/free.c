/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:48:57 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/28 16:58:21 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_array_len(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_file_data(t_cub *cub)
{
	if (cub->color.no_path)
		free(cub->color.no_path);
	if (cub->color.so_path)
		free(cub->color.so_path);
	if (cub->color.we_path)
		free(cub->color.we_path);
	if (cub->color.ea_path)
		free(cub->color.ea_path);
	if (cub->map->map2d)
		ft_array_free(cub->map->map2d);
	exit(1);
}

void	safe_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}
