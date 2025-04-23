/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:43:42 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/21 18:40:31 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	has_exact_commas(const char *s, int n)
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

static int	has_three_parts(char **color)
{
	return (color && ft_array_len(color) == 3);
}

static int	parts_are_digits(char **color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		if (!color[i] || color[i][0] == '\0')
			return (0);
		j = 0;
		while (color[i][j])
		{
			if (!ft_isdigit(color[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	values_in_range(char **color)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	return (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255);
}

int	is_valid_rgb_format(const char *str)
{
	char	**color;

	if (!has_exact_commas(str, 2))
		return (ft_error("RGB must contain exactly two commas.\n"));
	color = ft_split(str, ",");
	if (!has_three_parts(color))
	{
		ft_free_split(color);
		return (ft_error("RGB must have exactly 3 values.\n"));
	}
	if (!parts_are_digits(color))
	{
		ft_free_split(color);
		return (ft_error("RGB values must be numeric.\n"));
	}
	if (!values_in_range(color))
	{
		ft_free_split(color);
		return (ft_error("RGB values must be between 0 and 255.\n"));
	}
	ft_free_split(color);
	return (1);
}
