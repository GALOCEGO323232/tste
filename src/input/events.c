#include "cub3d.h"

int	close_window(t_cub *cub)
{
	cleanup_cub(cub);
	exit(0);
	return (0);
}

void	move_player(t_cub *cub, double move_speed, int direction)
{
	double	new_x;
	double	new_y;

	(void)move_speed;
	calculate_new_position(cub, &new_x, &new_y, direction);
	if (cub->map.grid[(int)cub->player.pos_y][(int)new_x] != '1')
		cub->player.pos_x = new_x;
	if (cub->map.grid[(int)new_y][(int)cub->player.pos_x] != '1')
		cub->player.pos_y = new_y;
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == KEY_ESC)
		close_window(cub);
	if (handle_movement_keys(keycode, cub))
		return (0);
	if (keycode == KEY_LEFT)
		rotate_player(cub, -0.05);
	else if (keycode == KEY_RIGHT)
		rotate_player(cub, 0.05);
	return (0);
}
