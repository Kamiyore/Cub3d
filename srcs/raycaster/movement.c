

#include "../../include/cub3d.h"

/*
	// To strafe perpendicular to the facing direction (θ),
		we rotate the forward vector by +90°:
	//   forward: (cosθ, sinθ)
	//   strafing right: (cos(θ+π/2), sin(θ+π/2))
	// Using the identities:
	//   cos(θ + π/2) = -sinθ
	//   sin(θ + π/2) =  cosθ
	// So the unit strafe vector is (-sinθ, cosθ).
	// We multiply by `sign` (+1 for right, -1 for left) and by MOVEMENT_SPEED.
	https://www.try-it.jp/chapters-6673/sections-6704/lessons-6717/
*/
static t_xy_i	compute_side_movement(t_cub *cub, int sign)
{
	double	move_x;
	double	move_y;
	t_xy_i	new_ply_position;

	move_x = -sign * sin(cub->ply->angle) * MOVEMENT_SPEED;
	move_y = sign * cos(cub->ply->angle) * MOVEMENT_SPEED;
	new_ply_position.x = roundf(cub->ply->pixel_x + move_x);
	new_ply_position.y = roundf(cub->ply->pixel_y + move_y);
	return (new_ply_position);
}

void	side_movement(t_cub *cub)
{
	t_xy_i	new_ply_position;

	if (cub->ply->left_right == MOVE_LEFT)
		new_ply_position = compute_side_movement(cub, -1);
	else if (cub->ply->left_right == MOVE_RIGHT)
		new_ply_position = compute_side_movement(cub, 1);
	else
		return ;
	move_player(cub, new_ply_position);
}
/*
	// Forward/back movement along the facing direction (θ):
	// The unit forward vector is (cosθ, sinθ).
	// To move forward, we use +1; to move backward, -1.
	// Multiply by MOVEMENT_SPEED to scale the movement per frame.
	// So (move_x, move_y) = (sign * cosθ * SPEED, sign * sinθ * SPEED).
*/
static t_xy_i	compute_front_back_movement(t_cub *cub, int sign)
{
	double	move_x;
	double	move_y;
	t_xy_i	new_ply_position;

	move_x = sign * cos(cub->ply->angle) * MOVEMENT_SPEED;
	move_y = sign * sin(cub->ply->angle) * MOVEMENT_SPEED;
	new_ply_position.x = roundf(cub->ply->pixel_x + move_x);
	new_ply_position.y = roundf(cub->ply->pixel_y + move_y);
	return (new_ply_position);
}

void	front_back_movement(t_cub *cub)
{
	t_xy_i	new_ply_position;

	if (cub->ply->up_down == MOVE_FORWARD)
		new_ply_position = compute_front_back_movement(cub, 1);
	else if (cub->ply->up_down == MOVE_BACK)
		new_ply_position = compute_front_back_movement(cub, -1);
	else
		return ;
	move_player(cub, new_ply_position);
}

void	movement(t_cub *cub)
{
	rotation(cub);
	side_movement(cub);
	front_back_movement(cub);
}
