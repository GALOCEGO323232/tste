#include "cub3d_bonus.h"

void	free_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->map.textures[i].img)
			mlx_destroy_image(cub->mlx, cub->map.textures[i].img);
		i++;
	}
}

void	free_sprites(t_cub *cub)
{
	if (cub->map.sprite_frames[0].img
		&& cub->map.sprite_frames[0].img != cub->map.textures[0].img)
		mlx_destroy_image(cub->mlx, cub->map.sprite_frames[0].img);
}

void	free_all_textures(t_cub *cub)
{
	free_textures(cub);
	free_sprites(cub);
}

void	free_texture_paths(t_map *map)
{
	if (map->no_texture)
	{
		free(map->no_texture);
		map->no_texture = NULL;
	}
	if (map->so_texture)
	{
		free(map->so_texture);
		map->so_texture = NULL;
	}
	if (map->we_texture)
	{
		free(map->we_texture);
		map->we_texture = NULL;
	}
	if (map->ea_texture)
	{
		free(map->ea_texture);
		map->ea_texture = NULL;
	}
}

void	free_map_grid(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}
