#include "cub3d.h"

void	cleanup_map_lines(t_list **map_lines)
{
	if (map_lines && *map_lines)
	{
		ft_lstclear(map_lines, free);
		*map_lines = NULL;
	}
}

int	cleanup_parse_error(t_cub *cub, t_list **map_lines)
{
	cleanup_map_lines(map_lines);
	return (cleanup_cub_return(cub));
}
