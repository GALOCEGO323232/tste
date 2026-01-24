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
	if (keycode == KEY_W)
		cub->keys.w = 1;
	if (keycode == KEY_S)
		cub->keys.s = 1;
	if (keycode == KEY_A)
		cub->keys.a = 1;
	if (keycode == KEY_D)
		cub->keys.d = 1;
	if (keycode == KEY_LEFT)
		cub->keys.left = 1;
	if (keycode == KEY_RIGHT)
		cub->keys.right = 1;
	if (keycode == KEY_M)
		toggle_minimap(cub);
	if (keycode == KEY_E)
		toggle_door(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W)
		cub->keys.w = 0;
	if (keycode == KEY_S)
		cub->keys.s = 0;
	if (keycode == KEY_A)
		cub->keys.a = 0;
	if (keycode == KEY_D)
		cub->keys.d = 0;
	if (keycode == KEY_LEFT)
		cub->keys.left = 0;
	if (keycode == KEY_RIGHT)
		cub->keys.right = 0;
	return (0);
}

void	process_keys(t_cub *cub)
{
	if (cub->keys.w)
		move_player(cub, MOVE_SPEED, 0);
	if (cub->keys.s)
		move_player(cub, MOVE_SPEED, 1);
	if (cub->keys.a)
		move_player(cub, MOVE_SPEED, 2);
	if (cub->keys.d)
		move_player(cub, MOVE_SPEED, 3);
	if (cub->keys.left)
		rotate_player(cub, -ROT_SPEED_KEYS);
	if (cub->keys.right)
		rotate_player(cub, ROT_SPEED_KEYS);
}
