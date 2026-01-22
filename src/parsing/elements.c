#include "cub3d.h"

static int	is_empty_line(char *line);
static int	parse_color(char *line, int *color);
static int	parse_texture(char *line, char **texture);
static int	check_identifier(char *line, int i, t_cub *cub);

int	parse_line(char *line, t_cub *cub)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return (0);
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (check_identifier(line, i, cub));
}

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
	int		end;

	if (*texture)
		return (ft_putstr_fd("Error\nDuplicate texture\n", 2), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i += 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	len = ft_strlen(line + i);
	if (len > 0 && line[i + len - 1] == '\n')
		len--;
	end = i + len - 1;
	while (end >= i && ft_isspace(line[end]))
		end--;
	len = end - i + 1;
	*texture = ft_substr(line, i, len);
	if (!*texture)
		return (ft_putstr_fd(ERR_MALLOC, 2), 1);
	return (0);
}

static int	parse_color(char *line, int *color)
{
	int	i;

	if (*color != -1)
		return (ft_putstr_fd("Error\nDuplicate color\n", 2), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	*color = parse_rgb(line + i);
	if (*color == -1)
		return (1);
	return (0);
}

static int	check_identifier(char *line, int i, t_cub *cub)
{
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
	return (2);
}
