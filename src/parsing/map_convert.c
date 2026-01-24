#include "cub3d.h"

static void	copy_content_and_update_width(t_list *tmp, char **grid,
				int *i, t_map *map);

int	add_line_to_list(t_list **map_lines, char *line)
{
	t_list	*new_node;
	char	*content;

	content = ft_strdup(line);
	if (!content)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	if (content[ft_strlen(content) - 1] == '\n')
		content[ft_strlen(content) - 1] = '\0';
	new_node = ft_lstnew(content);
	if (!new_node)
	{
		free(content);
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	}
	ft_lstadd_back(map_lines, new_node);
	return (0);
}

char	**convert_list_to_array(t_list *map_lines, t_map *map)
{
	int		size;
	char	**grid;
	int		i;
	t_list	*tmp;

	size = ft_lstsize(map_lines);
	map->height = size;
	grid = ft_calloc(size + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	i = 0;
	tmp = map_lines;
	while (tmp)
	{
		copy_content_and_update_width(tmp, grid, &i, map);
		tmp = tmp->next;
	}
	return (grid);
}

int	read_remaining_lines(int fd, t_list **map_lines)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (add_line_to_list(map_lines, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

static void	copy_content_and_update_width(t_list *tmp, char **grid,
	int *i, t_map *map)
{
	grid[*i] = tmp->content;
	tmp->content = NULL;
	if ((int)ft_strlen(grid[*i]) > map->width)
		map->width = ft_strlen(grid[*i]);
	(*i)++;
}
