#include "cub3d_bonus.h"

int	raycast(t_cub *cub)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(cub, &ray, x);
		calc_step(cub, &ray);
		perform_dda(cub, &ray);
		calc_wall_height(cub, &ray);
		draw_column(cub, x, &ray);
		x++;
	}
	return (0);
}
