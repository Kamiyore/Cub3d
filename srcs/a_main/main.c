/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:12:03 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/15 13:50:58 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	return (0);
}

int	valid_map_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".cub") != 0)
	{
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (argc != 2)
		return (ft_error("Usage: ./so_long name.ber"));
	if (!valid_map_file(argv[1]))
		return (ft_error("Invalid file format. Only '.ber'"));
	if (!parse_file(&config, argv[1]))
		return (1);
	if(!validate_map(&config))
	return(1);
	return (0);
}
