#include "cub3d.h"

int	close_window(t_cub *cub)
{
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
	// Todo: free map and textures
	exit(0);
	return (0);
}

void	rotate_player(t_cub *cub, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(rot_speed) - cub->player.dir_y * sin(rot_speed);
	cub->player.dir_y = old_dir_x * sin(rot_speed) + cub->player.dir_y * cos(rot_speed);
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(rot_speed) - cub->player.plane_y * sin(rot_speed);
	cub->player.plane_y = old_plane_x * sin(rot_speed) + cub->player.plane_y * cos(rot_speed);
}

void	move_player(t_cub *cub, double move_speed, int direction)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.pos_x;
	new_y = cub->player.pos_y;
	if (direction == 0) // W
	{
		new_x += cub->player.dir_x * move_speed;
		new_y += cub->player.dir_y * move_speed;
	}
	else if (direction == 1) // S
	{
		new_x -= cub->player.dir_x * move_speed;
		new_y -= cub->player.dir_y * move_speed;
	}
	else if (direction == 2) // A
	{
		new_x -= cub->player.plane_x * move_speed; // Perpendicular vector (strafe)
		new_y -= cub->player.plane_y * move_speed;
	}
	else if (direction == 3) // D
	{
		new_x += cub->player.plane_x * move_speed;
		new_y += cub->player.plane_y * move_speed;
	}

	// Simple collision check (check map grid)
	if (cub->map.grid[(int)cub->player.pos_y][(int)new_x] != '1')
		cub->player.pos_x = new_x;
	if (cub->map.grid[(int)new_y][(int)cub->player.pos_x] != '1')
		cub->player.pos_y = new_y;
}

int	key_press(int keycode, t_cub *cub)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.3; // Tuning might be needed
	rot_speed = 0.5;
	if (keycode == 65307) // ESC
		close_window(cub);
	else if (keycode == 119) // W
		move_player(cub, move_speed, 0);
	else if (keycode == 115) // S
		move_player(cub, move_speed, 1);
	else if (keycode == 97) // A
		move_player(cub, move_speed, 2);
	else if (keycode == 100) // D
		move_player(cub, move_speed, 3);
	else if (keycode == 65361) // Left Arrow
		rotate_player(cub, -rot_speed);
	else if (keycode == 65363) // Right Arrow
		rotate_player(cub, rot_speed);
	return (0);
}
