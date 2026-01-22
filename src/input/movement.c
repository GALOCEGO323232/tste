#include "cub3d.h"

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

