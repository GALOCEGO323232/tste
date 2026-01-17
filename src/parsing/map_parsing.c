/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/01/10 11:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_all_elements_set(t_map *map)
{
	if (!map->no_texture || !map->so_texture || !map->we_texture
		|| !map->ea_texture || map->floor_color == -1 || map->ceil_color == -1)
		return (0);
	return (1);
}

// Helper to append line to map grid (resizable array logic needed or linked list)
// For simplicity, we can use a linked list first then convert to array.
// But we don't have t_list in structs.h available easily unless we include libft struct
// which we do via cub3d.h -> libft.h

static int	add_line_to_list(t_list **map_lines, char *line)
{
	t_list	*new_node;
	char	*content;

	content = ft_strdup(line);
	if (!content)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	// remove newline if present
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

static char	**convert_list_to_array(t_list *map_lines, t_map *map)
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
		grid[i] = tmp->content; // Transfer ownership
		tmp->content = NULL; // Prevent double free logic if needed, but we will simple clear nodes
		if ((int)ft_strlen(grid[i]) > map->width)
			map->width = ft_strlen(grid[i]);
		tmp = tmp->next;
		i++;
	}
	return (grid);
}

int	read_map(int fd, char *first_line, t_cub *cub, t_list **map_lines)
{
	char	*line;

	if (!check_all_elements_set(&cub->map))
		return (ft_putstr_fd("Error\nMissing elements before map\n", 2), 1);
	
	if (add_line_to_list(map_lines, first_line))
		return (1);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		// Check for empty lines inside map?
		// For now just add everything, validate later
		if (add_line_to_list(map_lines, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	cub->map.grid = convert_list_to_array(*map_lines, &cub->map);
	if (!cub->map.grid)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	return (0);
}
