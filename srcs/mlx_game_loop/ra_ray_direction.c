/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_ray_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:19 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:56:16 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	look_left(float angle)
{
	return (angle > (M_PI_2) && angle < (3 * M_PI_2));
}

bool	look_right(float angle)
{
	return (!look_left(angle));
}

bool	look_down(float angle)
{
	return (angle > 0 && angle < M_PI);
}

bool	look_up(float angle)
{
	return (!look_down(angle));
}
