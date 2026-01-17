/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/01/10 11:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0');
}

static int	parse_texture(char *line, char **texture)
{
	int		i;
	int		len;

	if (*texture)
		return (ft_putstr_fd("Error\nDuplicate texture\n", 2), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i += 2; // Skip identifier
	while (line[i] && ft_isspace(line[i]))
		i++;
	len = ft_strlen(line + i);
	if (len > 0 && (line[i + len - 1] == '\n'))
		line[i + len - 1] = '\0';
	*texture = ft_strdup(line + i);
	if (!*texture)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	return (0);
}

static int	parse_rgb(char *line)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		i;

	split = ft_split(line, ',');
	if (!split)
		return (ft_putstr_fd(ERR_MALLOC, 2), -1);
	i = 0;
	while (split[i])
		i++;
	if (i != 3)
		return (ft_putstr_fd("Error\nInvalid color format\n", 2), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	// Free split
	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putstr_fd("Error\nInvalid color value\n", 2), -1);
	return (r << 16 | g << 8 | b);
}

static int	parse_color(char *line, int *color)
{
	int	i;

	if (*color != -1)
		return (ft_putstr_fd("Error\nDuplicate color\n", 2), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i++; // Skip 'F' or 'C'
	while (line[i] && ft_isspace(line[i]))
		i++;
	*color = parse_rgb(line + i);
	if (*color == -1)
		return (1);
	return (0);
}

int	parse_line(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp(line + i, "NO", 2))
		return (parse_texture(line + i, &cub->map.no_texture));
	if (!ft_strncmp(line + i, "SO", 2))
		return (parse_texture(line + i, &cub->map.so_texture));
	if (!ft_strncmp(line + i, "WE", 2))
		return (parse_texture(line + i, &cub->map.we_texture));
	if (!ft_strncmp(line + i, "EA", 2))
		return (parse_texture(line + i, &cub->map.ea_texture));
	if (!ft_strncmp(line + i, "F", 1))
		return (parse_color(line + i, &cub->map.floor_color));
	if (!ft_strncmp(line + i, "C", 1))
		return (parse_color(line + i, &cub->map.ceil_color));
	// Check for map start or error
	return (2);
}
