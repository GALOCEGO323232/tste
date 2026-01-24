#include "cub3d.h"

static int	check_chars_and_player(t_map *map);
static int	check_player_at_position(t_map *map, int i, int j,
				int *player_count);

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_map(t_map *map)
{
	if (check_chars_and_player(map))
		return (1);
	if (check_walls(map))
		return (1);
	return (0);
}

static int	check_player_at_position(t_map *map, int i, int j,
	int *player_count)
{
	if (is_player(map->grid[i][j]))
	{
		(*player_count)++;
		map->player_x = j;
		map->player_y = i;
		map->player_dir = map->grid[i][j];
	}
	return (0);
}

static int	check_chars_and_player(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (!is_valid_char(map->grid[i][j]))
				return (ft_putstr_fd("Error\nInvalid character in map\n",
						2), 1);
			check_player_at_position(map, i, j, &player_count);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_putstr_fd("Error\nInvalid player count\n", 2), 1);
	return (0);
}
