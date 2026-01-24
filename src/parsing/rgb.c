#include "cub3d.h"

static int	validate_split(char **split);
static void	free_split_array(char **split);
static int	get_rgb_values(char **split, int *r, int *g, int *b);
static int	is_valid_rgb_value(char *str);

int	parse_rgb(char *line)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	split = ft_split(line, ',');
	if (!split)
		return (ft_putstr_fd(ERR_MALLOC, 2), -1);
	if (!validate_split(split))
		return (-1);
	return (get_rgb_values(split, &r, &g, &b));
}

static int	is_valid_rgb_value(char *str)
{
	int		i;
	size_t	num_start;
	size_t	num_len;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	num_start = i;
	num_len = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		num_len++;
		i++;
	}
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] || num_len > 3)
		return (0);
	if (num_len == 3 && ft_strncmp(&str[num_start], "255", 3) > 0)
		return (0);
	return (1);
}

static int	get_rgb_values(char **split, int *r, int *g, int *b)
{
	*r = ft_atoi(split[0]);
	*g = ft_atoi(split[1]);
	*b = ft_atoi(split[2]);
	free_split_array(split);
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (ft_putstr_fd("Error\nColor range must be 0-255\n", 2), -1);
	return ((*r << 16) | (*g << 8) | *b);
}

static void	free_split_array(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

static int	validate_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_split_array(split);
		return (ft_putstr_fd("Error\nInvalid color format\n", 2), 0);
	}
	if (!is_valid_rgb_value(split[0]) || !is_valid_rgb_value(split[1])
		|| !is_valid_rgb_value(split[2]))
	{
		free_split_array(split);
		return (ft_putstr_fd("Error\nRGB must be numeric\n", 2), 0);
	}
	return (1);
}
