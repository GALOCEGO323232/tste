#include "cub3d_bonus.h"

int	render_loop(t_cub *cub)
{
	process_keys(cub);
	raycast(cub);
	render_sprites(cub);
	render_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	return (0);
}
