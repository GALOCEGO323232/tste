#include "cub3d_bonus.h"

static int	handle_parse_error(int fd, char *line);
static int	parse_file_lines(int fd, t_cub *cub, t_list **map_lines);
static int	process_line(int fd, char *line, t_cub *cub, t_list **map_lines);
static int	handle_map_start(int fd, char *line, t_cub *cub,
				t_list **map_lines);

int	parse_cub_file(char *file, t_cub *cub)
{
	int		fd;
	t_list	*map_lines;

	map_lines = NULL;
	init_map(&cub->map);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(ERR_FILE, 2), 1);
	if (parse_file_lines(fd, cub, &map_lines))
		return (close(fd), cleanup_parse_error(cub, &map_lines));
	close(fd);
	if (!cub->map.grid)
	{
		ft_putstr_fd("Error\nNo map found\n", 2);
		return (cleanup_parse_error(cub, &map_lines));
	}
	ft_lstclear(&map_lines, free);
	if (validate_map(&cub->map))
		return (cleanup_cub_return(cub));
	if (parse_doors(&cub->map))
		return (cleanup_cub_return(cub));
	if (parse_sprites(&cub->map))
		return (cleanup_cub_return(cub));
	return (0);
}

static int	handle_map_start(int fd, char *line, t_cub *cub,
	t_list **map_lines)
{
	if (read_map(fd, line, cub, map_lines))
	{
		free(line);
		close(fd);
		return (1);
	}
	free(line);
	return (2);
}

static int	handle_parse_error(int fd, char *line)
{
	free(line);
	get_next_line(-1);
	close(fd);
	return (1);
}

static int	process_line(int fd, char *line, t_cub *cub, t_list **map_lines)
{
	int	ret;

	ret = parse_line(line, cub);
	if (ret == 1)
		return (handle_parse_error(fd, line));
	if (ret == 2)
	{
		ret = handle_map_start(fd, line, cub, map_lines);
		if (ret == 1)
		{
			get_next_line(-1);
			return (1);
		}
		return (2);
	}
	return (0);
}

static int	parse_file_lines(int fd, t_cub *cub, t_list **map_lines)
{
	char	*line;
	int		ret;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ret = process_line(fd, line, cub, map_lines);
		if (ret == 1)
			return (1);
		if (ret == 2)
			break ;
		free(line);
	}
	return (0);
}
