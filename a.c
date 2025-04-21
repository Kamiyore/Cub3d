

// #include "minicub.h"
#include "include/cub3d.h"
#include "srcs/raycaster/minicub.h"
#include <math.h>
#include <stdio.h>

int	main(void)
{
	double	degrees;
	double	radians;
	double	result;

	degrees = 45.0;
	radians = degrees * M_PI / 180.0;
	result = tan(radians);
	printf("tan(%.0f°) = %f\n", degrees, result);
	return (0);
}
