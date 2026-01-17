#include "cub3d.h"

static void	init_map(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = -1;
	map->ceil_color = -1;
	map->grid = NULL;
	map->player_dir = 0;
}

int	parse_cub_file(char *file, t_cub *cub)
{
	int		fd;
	char	*line;

	int		ret;
	t_list	*map_lines;

	map_lines = NULL;
	init_map(&cub->map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(ERR_FILE, 2);
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = parse_line(line, cub);
		if (ret == 1)
		{
			free(line);
			close(fd);
			return (1);
		}
		else if (ret == 2)
		{
			if (read_map(fd, line, cub, &map_lines))
			{
				free(line);
				ft_lstclear(&map_lines, free);
				close(fd);
				return (1);
			}
			free(line);
			break ; // Map read completely
		}
		free(line);
	}
	close(fd);
	if (!cub->map.grid) // If map was never read
		return (ft_putstr_fd("Error\nNo map found\n", 2), 1);
	ft_lstclear(&map_lines, free);
	if (validate_map(&cub->map))
		return (1);
	return (0);
}
