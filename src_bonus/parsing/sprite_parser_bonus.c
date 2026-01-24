#include "cub3d_bonus.h"

static int	count_sprites(t_map *map);
static void	store_sprite_positions(t_map *map);

int	parse_sprites(t_map *map)
{
	int	count;

	count = count_sprites(map);
	if (count == 0)
	{
		map->sprites = NULL;
		map->num_sprites = 0;
		return (0);
	}
	map->sprites = malloc(sizeof(t_sprite_pos) * count);
	if (!map->sprites)
		return (1);
	map->num_sprites = count;
	store_sprite_positions(map);
	return (0);
}

static int	count_sprites(t_map *map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width && map->grid[y][x])
		{
			if (map->grid[y][x] == 'X')
				count++;
		}
	}
	return (count);
}

static void	store_sprite_positions(t_map *map)
{
	int	y;
	int	x;
	int	idx;

	idx = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width && map->grid[y][x])
		{
			if (map->grid[y][x] == 'X')
			{
				map->sprites[idx].x = x + 0.5;
				map->sprites[idx].y = y + 0.5;
				map->sprites[idx].dist = 0.0;
				idx++;
			}
		}
	}
}
