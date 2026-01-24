#include "cub3d_bonus.h"

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
}

void	error_exit_cleanup(t_cub *cub, char *msg)
{
	ft_putstr_fd(msg, 2);
	cleanup_cub(cub);
	exit(1);
}
