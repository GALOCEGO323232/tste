/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/01/10 11:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
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
				return (ft_putstr_fd("Error\nInvalid character in map\n", 2), 1);
			if (is_player(map->grid[i][j]))
			{
				player_count++;
				map->player_x = j;
				map->player_y = i;
				map->player_dir = map->grid[i][j];
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_putstr_fd("Error\nInvalid player count\n", 2), 1);
	return (0);
}

// Flood fill or wall check
// Simple approach: Check if every 0 or player is surrounded by something that is not space/null
// Better approach: Flood fill from player check if it reaches out of bounds or space

static int	flood_fill(char **temp_grid, int x, int y, int height, int width)
{
	if (x < 0 || x >= width || y < 0 || y >= height
		|| temp_grid[y][x] == ' ')
		return (1); // Error: reached outside or space
	if (temp_grid[y][x] == '1' || temp_grid[y][x] == 'V')
		return (0); // Wall or visited
	temp_grid[y][x] = 'V'; // Mark visited
	if (flood_fill(temp_grid, x + 1, y, height, width)) return (1);
	if (flood_fill(temp_grid, x - 1, y, height, width)) return (1);
	if (flood_fill(temp_grid, x, y + 1, height, width)) return (1);
	if (flood_fill(temp_grid, x, y - 1, height, width)) return (1);
	return (0);
}

// We need a padded grid or robust bounds checking for flood fill locally because rows have different lengths
// map->grid rows are not padded to map->width with spaces in my current implementation.
// I should probably pad them or handle it in flood_fill.
// Let's create a temporary padded copy for flood fill.

static char	**copy_grid_padded(t_map *map)
{
	char	**new_grid;
	int		i;
	int		j;

	new_grid = malloc(sizeof(char *) * (map->height + 1));
	if (!new_grid)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		new_grid[i] = malloc(map->width + 1);
		if (!new_grid[i])
		{
			// Free previous
			while (--i >= 0) free(new_grid[i]);
			free(new_grid);
			return (NULL);
		}
		ft_strlcpy(new_grid[i], map->grid[i], map->width + 1);
		// Pad with spaces
		j = ft_strlen(map->grid[i]);
		while (j < map->width)
			new_grid[i][j++] = ' ';
		new_grid[i][j] = '\0';
		i++;
	}
	new_grid[i] = NULL;
	return (new_grid);
}

static void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
		free(grid[i++]);
	free(grid);
}

static int	check_walls(t_map *map)
{
	char	**temp_grid;
	int		ret;

	temp_grid = copy_grid_padded(map);
	if (!temp_grid)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	ret = flood_fill(temp_grid, map->player_x, map->player_y, map->height, map->width);
	free_grid(temp_grid);
	if (ret)
		return (ft_putstr_fd("Error\nMap is not closed\n", 2), 1);
	return (0);
}

int	validate_map(t_map *map)
{
	if (check_chars_and_player(map))
		return (1);
	if (check_walls(map))
		return (1);
	return (0);
}
