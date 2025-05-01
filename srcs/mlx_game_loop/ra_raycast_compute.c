/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ra_raycast_compute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oyuhi <oyuhi@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:07:14 by oyuhi             #+#    #+#             */
/*   Updated: 2025/04/30 18:50:59 by oyuhi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
		// tan(θ) = opposite (y) / adjacent (x), so x = y / tan(θ)
	// Calculate x_step by dividing TILE_SIZE (y-direction) by tan(θ).
*/
float	compute_adjacent(float opposite, float angle)
{
	return (opposite / tan(angle));
}

/*
	// tan(θ) = opposite (y) / adjacent (x), so y = x * tan(θ)
	// Calculate y_step (opposite) by multiplying TILE_SIZE
	(adjacent, x-direction) by tan(θ).
*/
float	compute_opposite(float adjacent, float angle)
{
	return (adjacent * tan(angle));
}

/*
	Pythagoras’s theorem a² + b² = c²
*/
float	compute_hypotenuse(float opposite, float adjacent)
{
	return (sqrt(pow(opposite, 2) + pow(adjacent, 2)));
}
