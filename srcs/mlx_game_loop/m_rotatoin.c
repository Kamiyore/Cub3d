/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_rotatoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:45 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:55:33 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	rotate_player(t_cub *cub, int sign)
{
	cub->ply->angle += (sign * ROTATION_SPEED);
	cub->ply->angle = normalize_angle(cub->ply->angle);
}

void	rotation(t_cub *cub)
{
	if (cub->ply->rotation == ROTATE_RIGHT)
		rotate_player(cub, 1);
	else if (cub->ply->rotation == ROTATE_LEFT)
		rotate_player(cub, -1);
}
