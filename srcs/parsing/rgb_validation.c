/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:43:42 by knemcova          #+#    #+#             */
/*   Updated: 2025/05/01 12:42:35 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*get_clean_rgb_line(const char *str, int *error)
{
	char	*line;

	line = trim_ws(str);
	if (!has_exact_commas(line, 2))
	{
		*error = ft_error("RGB must contain exactly two commas.\n");
		free(line);
		return (NULL);
	}
	return (line);
}

static char	**split_and_trim_rgb_parts(char *line, int *error)
{
	char	**parts;
	char	*tmp;
	int		i;

	parts = ft_split(line, ",");
	if (!has_three_parts(parts))
	{
		ft_array_free(parts);
		*error = ft_error("RGB must have exactly 3 values.\n");
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		tmp = trim_ws(parts[i]);
		free(parts[i]);
		parts[i++] = tmp;
	}
	return (parts);
}

static char	**prepare_rgb_parts(const char *str, int *error)
{
	char	*line;
	char	**parts;

	*error = 0;
	line = get_clean_rgb_line(str, error);
	if (*error)
		return (NULL);
	parts = split_and_trim_rgb_parts(line, error);
	free(line);
	if (*error && parts)
		ft_array_free(parts);
	return (parts);
}

static int	validate_rgb_parts(char **parts)
{
	if (parts_are_digits(parts) != 0)
		return (ft_error("RGB values must be numeric.\n"));
	if (!values_in_range(parts))
		return (ft_error("RGB values must be between 0 and 255.\n"));
	return (0);
}

int	is_valid_rgb_format(const char *str)
{
	int		error;
	char	**parts;

	error = 0;
	parts = prepare_rgb_parts(str, &error);
	if (error || !parts)
		return (error);
	error = validate_rgb_parts(parts);
	ft_array_free(parts);
	return (error);
}
