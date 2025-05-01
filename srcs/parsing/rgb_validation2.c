/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:40:16 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 12:49:11 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	has_exact_commas(const char *s, int n)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == ',')
			count++;
		s++;
	}
	return (count == n);
}

int	has_three_parts(char **color)
{
	return (color && ft_array_len(color) == 3);
}

int	parts_are_digits(char **color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (!color[i] || color[i][0] == '\0')
			return (-1);
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	values_in_range(char **color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}
