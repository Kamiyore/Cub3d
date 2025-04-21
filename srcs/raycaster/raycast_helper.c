

#include "minicub.h"

//#################################################################################//
//############################# THE RAYCASTING HELPER #############################//
//#################################################################################//

// int	get_quandrant(float angle)
// {
// 	if (angle >= 0 && angle < M_PI / 2)
// 		return (1);
// 	else if (angle >= M_PI / 2 && angle < M_PI)
// 		return (2);
// 	else if (angle >= M_PI && angle < 3 * M_PI / 2)
// 		return (3);
// 	else
// 		return (4);
// }

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

int	is_wall(t_cub *cub, float inter_x, float inter_y)
{
	int		map_index_y;
	int		map_index_x;
	char	**map2d;

	map2d = cub->map->map2d;
	map_index_y = floor(inter_y / TILE_SIZE);
	map_index_x = floor(inter_x / TILE_SIZE);
	if (map_index_y < 0 || map_index_y >= cub->map->height || map_index_x < 0
		|| map_index_x >= cub->map->width)
		return (1);
	if (map2d[map_index_y] == NULL
		|| map_index_x >= (int)ft_strlen(map2d[map_index_y]))
		return (1);
	return (map2d[map_index_y][map_index_x] == '1');
}

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
	return (sqrt(opposite * opposite + adjacent * adjacent));
}
