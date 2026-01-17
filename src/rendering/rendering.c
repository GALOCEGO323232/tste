#include "cub3d.h"

void	load_texture(t_cub *cub, int idx, char *path)
{
	t_img	*tex;

	tex = &cub->map.textures[idx];
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		error_exit("Error\nFailed to load texture\n"); // Should handle gracefully
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
}

void	init_textures(t_cub *cub)
{
	load_texture(cub, 0, cub->map.no_texture);
	load_texture(cub, 1, cub->map.so_texture);
	load_texture(cub, 2, cub->map.we_texture);
	load_texture(cub, 3, cub->map.ea_texture);
}

int	render_loop(t_cub *cub)
{
	raycast(cub);
	return (0);
}
