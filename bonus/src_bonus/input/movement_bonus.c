#include "cub3d_bonus.h"

void	calculate_new_position(t_cub *cub, double *new_x, double *new_y,
	int direction)
{
	double	move_speed;

	move_speed = 0.1;
	*new_x = cub->player.pos_x;
	*new_y = cub->player.pos_y;
	if (direction == 0)
	{
		*new_x += cub->player.dir_x * move_speed;
		*new_y += cub->player.dir_y * move_speed;
	}
	else if (direction == 1)
	{
		*new_x -= cub->player.dir_x * move_speed;
		*new_y -= cub->player.dir_y * move_speed;
	}
	else if (direction == 2)
	{
		*new_x -= cub->player.plane_x * move_speed;
		*new_y -= cub->player.plane_y * move_speed;
	}
	else if (direction == 3)
	{
		*new_x += cub->player.plane_x * move_speed;
		*new_y += cub->player.plane_y * move_speed;
	}
}

int	handle_movement_keys(int keycode, t_cub *cub)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		return (move_player(cub, 0.1, 0), 1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		return (move_player(cub, 0.1, 1), 1);
	else if (keycode == KEY_A)
		return (move_player(cub, 0.1, 2), 1);
	else if (keycode == KEY_D)
		return (move_player(cub, 0.1, 3), 1);
	return (0);
}
