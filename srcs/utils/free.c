/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:48:57 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/18 19:58:20 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_array_len(char **array)
{
	int i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_file_data(t_file_data *file)
{
	if (file->color.no_path)
		free(file->color.no_path);
	if (file->color.so_path)
		free(file->color.so_path);
	if (file->color.we_path)
		free(file->color.we_path);
	if (file->color.ea_path)
		free(file->color.ea_path);
	if (file->map.map)
		ft_free_split(file->map.map);
	exit(1);
}
