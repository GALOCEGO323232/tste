#include "cub3d_bonus.h"

static int	flood_fill_scan(t_flood_params *params, int sx, int sy);
static int	mark_neighbors(t_flood_params *params);
static int	check_boundaries(t_flood_params *params);

int	check_walls(t_map *map)
{
	char			**temp_grid;
	int				ret;
	t_flood_params	params;

	temp_grid = copy_grid_padded(map);
	if (!temp_grid)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	params.grid = temp_grid;
	params.height = map->height;
	params.width = map->width;
	ret = flood_fill_scan(&params, map->player_x, map->player_y);
	free_grid(temp_grid);
	if (ret)
		return (ft_putstr_fd("Error\nMap is not closed\n", 2), 1);
	return (0);
}

static int	flood_fill_scan(t_flood_params *params, int sx, int sy)
{
	int	changed;

	if (sx < 0 || sy < 0 || sy >= params->height || sx >= params->width)
		return (1);
	params->grid[sy][sx] = 'V';
	changed = 1;
	while (changed)
	{
		changed = mark_neighbors(params);
		if (changed < 0)
			return (1);
	}
	return (check_boundaries(params));
}

static int	mark_neighbors(t_flood_params *params)
{
	int	x;
	int	y;
	int	changed;
	int	result;

	changed = 0;
	y = -1;
	while (++y < params->height)
	{
		x = -1;
		while (++x < params->width && params->grid[y][x])
		{
			if (params->grid[y][x] == 'V')
			{
				result = mark_adjacent_cells(params, x, y);
				if (result < 0)
					return (-1);
				if (result > 0)
					changed = 1;
			}
		}
	}
	return (changed);
}

static int	check_boundaries(t_flood_params *params)
{
	int	x;
	int	y;

	y = -1;
	while (++y < params->height)
	{
		x = -1;
		while (++x < params->width && params->grid[y][x])
		{
			if (params->grid[y][x] == 'V' || params->grid[y][x] == 'S')
			{
				if (x == 0 || y == 0 || x == params->width - 1
					|| y == params->height - 1)
					return (1);
			}
		}
	}
	return (0);
}
