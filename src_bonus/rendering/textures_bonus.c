#include "cub3d_bonus.h"

static void	load_texture(t_cub *cub, int idx, char *path);
static void	load_sprite_frames(t_cub *cub);

void	init_textures(t_cub *cub)
{
	load_texture(cub, 0, cub->map.no_texture);
	load_texture(cub, 1, cub->map.so_texture);
	load_texture(cub, 2, cub->map.we_texture);
	load_texture(cub, 3, cub->map.ea_texture);
	load_sprite_frames(cub);
}

static void	load_texture(t_cub *cub, int idx, char *path)
{
	t_img	*tex;

	tex = &cub->map.textures[idx];
	tex->img = mlx_xpm_file_to_image(cub->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		error_exit_cleanup(cub, "Error\nFailed to load texture\n");
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
}

static void	load_sprite_frames(t_cub *cub)
{
	t_img	*sprite;

	sprite = &cub->map.sprite_frames[0];
	sprite->img = mlx_xpm_file_to_image(cub->mlx,
			"./textures/sprite1.xpm", &sprite->width, &sprite->height);
	if (!sprite->img)
	{
		cub->map.sprite_frames[0] = cub->map.textures[0];
		cub->map.sprite_frames[1] = cub->map.textures[1];
		cub->map.sprite_frames[2] = cub->map.textures[2];
		cub->map.sprite_frames[3] = cub->map.textures[3];
		return ;
	}
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bpp,
			&sprite->line_len, &sprite->endian);
	cub->map.sprite_frames[1] = cub->map.sprite_frames[0];
	cub->map.sprite_frames[2] = cub->map.sprite_frames[0];
	cub->map.sprite_frames[3] = cub->map.sprite_frames[0];
}
