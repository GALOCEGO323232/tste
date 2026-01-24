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
	else if (keycode == KEY_W || keycode == KEY_UP)
		cub->input.w = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->input.s = 1;
	else if (keycode == KEY_A)
		cub->input.a = 1;
	else if (keycode == KEY_D)
		cub->input.d = 1;
	else if (keycode == KEY_LEFT)
		cub->input.left = 1;
	else if (keycode == KEY_RIGHT)
		cub->input.right = 1;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cub->input.w = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cub->input.s = 0;
	else if (keycode == KEY_A)
		cub->input.a = 0;
	else if (keycode == KEY_D)
		cub->input.d = 0;
	else if (keycode == KEY_LEFT)
		cub->input.left = 0;
	else if (keycode == KEY_RIGHT)
		cub->input.right = 0;
	return (0);
}
