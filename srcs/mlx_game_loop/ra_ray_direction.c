
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