

#include "../../include/cub3d.h"

int	mlx_key_press(int keycode, void *param)
{
	t_cub	*cub;

	cub = param;
	if (keycode == XK_Escape)
		exit_game(cub);
	else if (keycode == XK_a)
		cub->ply->left_right = MOVE_LEFT;
	else if (keycode == XK_d)
		cub->ply->left_right = MOVE_RIGHT;
	else if (keycode == XK_s)
		cub->ply->up_down = MOVE_BACK;
	else if (keycode == XK_w)
		cub->ply->up_down = MOVE_FORWARD;
	else if (keycode == XK_Left)
		cub->ply->rotation = ROTATE_LEFT;
	else if (keycode == XK_Right)
		cub->ply->rotation = ROTATE_RIGHT;
	return (0);
}

int	mlx_key_release(int keycode, void *param)
{
	t_cub *cub = param;

	if (keycode == XK_a || keycode == XK_d)
		cub->ply->left_right = 0;
	else if (keycode == XK_w || keycode == XK_s)
		cub->ply->up_down = 0;
	else if (keycode == XK_Left || keycode == XK_Right)
		cub->ply->rotation = 0;
	return (0);
}

int	x_button_exit(t_cub *cub)
{
	exit_game(cub);
	return (0);
}
