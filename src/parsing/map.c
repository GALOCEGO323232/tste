#include "cub3d.h"

static int	check_all_elements_set(t_map *map);

int	read_map(int fd, char *first_line, t_cub *cub, t_list **map_lines)
{
	if (!check_all_elements_set(&cub->map))
	{
		ft_putstr_fd("Error\nMissing elements before map\n", 2);
		return (cleanup_cub_return(cub));
	}
	if (add_line_to_list(map_lines, first_line))
		return (cleanup_cub_return(cub));
	if (read_remaining_lines(fd, map_lines))
		return (cleanup_cub_return(cub));
	cub->map.grid = convert_list_to_array(*map_lines, &cub->map);
	if (!cub->map.grid)
	{
		ft_putstr_fd(ERR_MALLOC, 2);
		return (cleanup_cub_return(cub));
	}
	return (0);
}

static int	check_all_elements_set(t_map *map)
{
	if (!map->no_texture || !map->so_texture || !map->we_texture
		|| !map->ea_texture || map->floor_color == -1
		|| map->ceil_color == -1)
		return (0);
	return (1);
}
