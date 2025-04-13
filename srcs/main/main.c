/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knemcova <knemcova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:12:03 by knemcova          #+#    #+#             */
/*   Updated: 2025/04/13 14:00:21 by knemcova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		printf("Usage: ./cub3D name.cub");
	if (!valid_map_file(argv[1]))
		printf("Invalid file format. Only '.cub'");
}
