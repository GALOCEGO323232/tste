#include "cub3d_bonus.h"

static int	check_point_collision(t_cub *cub, double x, double y);

int	check_collision(t_cub *cub, double new_x, double new_y)
{
	double	offset;

	offset = COLLISION_DIST;
	if (check_point_collision(cub, new_x + offset, new_y + offset))
		return (1);
	if (check_point_collision(cub, new_x - offset, new_y + offset))
		return (1);
	if (check_point_collision(cub, new_x + offset, new_y - offset))
		return (1);
	if (check_point_collision(cub, new_x - offset, new_y - offset))
		return (1);
	return (0);
}

static int	check_point_collision(t_cub *cub, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= cub->map.width
		|| map_y < 0 || map_y >= cub->map.height)
		return (1);
	if (cub->map.grid[map_y][map_x] == '1'
		|| cub->map.grid[map_y][map_x] == 'D')
		return (1);
	return (0);
}
