#include "cub3d.h"

int	render_loop(t_cub *cub)
{
	if (cub->input.w)
		move_player(cub, 0.1, 0);
	if (cub->input.s)
		move_player(cub, 0.1, 1);
	if (cub->input.a)
		move_player(cub, 0.1, 2);
	if (cub->input.d)
		move_player(cub, 0.1, 3);
	if (cub->input.left)
		rotate_player(cub, -0.05);
	if (cub->input.right)
		rotate_player(cub, 0.05);
	raycast(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->screen.img, 0, 0);
	return (0);
}
