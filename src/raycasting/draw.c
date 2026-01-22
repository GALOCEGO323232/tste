#include "cub3d.h"

void	draw_ceiling(t_cub *cub, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		my_mlx_pixel_put(&cub->screen, x, y, cub->map.ceil_color);
		y++;
	}
}

void	draw_floor(t_cub *cub, int x, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&cub->screen, x, y, cub->map.floor_color);
		y++;
	}
}

void	draw_wall(t_cub *cub, int x, t_ray *ray)
{
	int		y;
	int		color;
	int		tex_y;
	t_img	*tex;
	char	*dst;

	tex = &cub->map.textures[ray->tex_num];
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (tex->height - 1);
		ray->tex_pos += ray->step;
		dst = tex->addr + (tex_y * tex->line_len + ray->tex_x * (tex->bpp / 8));
		color = *(unsigned int *)dst;
		my_mlx_pixel_put(&cub->screen, x, y, color);
		y++;
	}
}

void	draw_column(t_cub *cub, int x, t_ray *ray)
{
	draw_ceiling(cub, x, ray->draw_start);
	draw_wall(cub, x, ray);
	draw_floor(cub, x, ray->draw_end);
}
