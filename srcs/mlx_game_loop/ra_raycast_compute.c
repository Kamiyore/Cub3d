

#include "../../include/cub3d.h"

/*
		// tan(θ) = opposite (y) / adjacent (x), so x = y / tan(θ)
	// Calculate x_step by dividing TILE_SIZE (y-direction) by tan(θ).
*/
myfloat	compute_adjacent(float opposite, float angle)
{
	return (opposite / tan(angle));
}

/*
	// tan(θ) = opposite (y) / adjacent (x), so y = x * tan(θ)
	// Calculate y_step (opposite) by multiplying TILE_SIZE
	(adjacent, x-direction) by tan(θ).
*/
myfloat	compute_opposite(float adjacent, float angle)
{
	return (adjacent * tan(angle));
}

/*
	Pythagoras’s theorem a² + b² = c²
*/
myfloat	compute_hypotenuse(myfloat opposite, myfloat adjacent)
{
	return (sqrt(pow(opposite, 2) + pow(adjacent, 2)));
}
