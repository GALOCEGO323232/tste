#include "cub3d_bonus.h"

int	check_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		ft_putstr_fd(ERR_ARGS, 2);
		return (1);
	}
	len = ft_strlen(argv[1]);
	if (len < 5)
	{
		ft_putstr_fd(ERR_EXT, 2);
		return (1);
	}
	if (ft_strcmp(argv[1] + len - 4, ".cub") != 0)
	{
		ft_putstr_fd(ERR_EXT, 2);
		return (1);
	}
	return (0);
}
