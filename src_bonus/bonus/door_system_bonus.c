#include "cub3d_bonus.h"

static int	get_door_at(t_cub *cub, int x, int y);

void	toggle_door(t_cub *cub)
{
	int		check_x;
	int		check_y;
	int		door_idx;

	check_x = (int)(cub->player.pos_x + cub->player.dir_x * 1.5);
	check_y = (int)(cub->player.pos_y + cub->player.dir_y * 1.5);
	if (check_x < 0 || check_x >= cub->map.width
		|| check_y < 0 || check_y >= cub->map.height)
		return ;
	if (cub->map.grid[check_y][check_x] != 'D'
		&& cub->map.grid[check_y][check_x] != 'O')
		return ;
	door_idx = get_door_at(cub, check_x, check_y);
	if (door_idx >= 0)
	{
		cub->map.doors[door_idx].is_open = !cub->map.doors[door_idx].is_open;
		if (cub->map.doors[door_idx].is_open)
			cub->map.grid[check_y][check_x] = 'O';
		else
			cub->map.grid[check_y][check_x] = 'D';
	}
}

static int	get_door_at(t_cub *cub, int x, int y)
{
	int	i;

	i = -1;
	while (++i < cub->map.num_doors)
	{
		if (cub->map.doors[i].x == x && cub->map.doors[i].y == y)
			return (i);
	}
	return (-1);
}

int	is_door_open(t_cub *cub, int x, int y)
{
	int	i;

	i = -1;
	while (++i < cub->map.num_doors)
	{
		if (cub->map.doors[i].x == x && cub->map.doors[i].y == y)
			return (cub->map.doors[i].is_open);
	}
	return (0);
}
