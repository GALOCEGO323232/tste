#include "cub3d.h"

static void	free_map_grid(t_map *map);
static void	free_texture_paths(t_map *map);
static void	free_textures(t_cub *cub);

void	cleanup_cub(t_cub *cub)
{
	if (cub->screen.img)
		mlx_destroy_image(cub->mlx, cub->screen.img);
	free_textures(cub);
	free_texture_paths(&cub->map);
	free_map_grid(&cub->map);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}

int	cleanup_cub_return(t_cub *cub)
{
	cleanup_cub(cub);
	return (1);
}

static void	free_textures(t_cub *cub)
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

static void	free_texture_paths(t_map *map)
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

static void	free_map_grid(t_map *map)
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
