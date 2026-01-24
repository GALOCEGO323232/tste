#include "cub3d_bonus.h"

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
	if (!check_collision(cub, new_x, cub->player.pos_y))
		cub->player.pos_x = new_x;
	if (!check_collision(cub, cub->player.pos_x, new_y))
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
	else if (keycode == KEY_M)
		toggle_minimap(cub);
	else if (keycode == KEY_E)
		toggle_door(cub);
	return (0);
}
