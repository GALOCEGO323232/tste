#include "cub3d_bonus.h"

void	my_mlx_pixel_put(t_screen *screen, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = screen->addr + (y * screen->line_len + x * (screen->bpp / 8));
	*(unsigned int *)dst = color;
}
