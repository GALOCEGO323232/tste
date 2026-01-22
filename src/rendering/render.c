#include "cub3d.h"

int	render_loop(t_cub *cub)
{
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	return (0);
}
