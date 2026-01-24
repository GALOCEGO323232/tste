#include "cub3d_bonus.h"

void	init_cub(t_cub *cub)
{
	cub->mlx = NULL;
	cub->win = NULL;
	cub->screen.img = NULL;
	cub->screen.addr = NULL;
	cub->map.no_texture = NULL;
	cub->map.so_texture = NULL;
	cub->map.we_texture = NULL;
	cub->map.ea_texture = NULL;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.floor_color = -1;
	cub->map.ceil_color = -1;
	cub->map.player_dir = 0;
	cub->map.textures[0].img = NULL;
	cub->map.textures[1].img = NULL;
	cub->map.textures[2].img = NULL;
	cub->map.textures[3].img = NULL;
	cub->map.minimap.enabled = 1;
	cub->map.minimap.size = MINIMAP_SIZE;
	cub->map.minimap.scale = MINIMAP_SCALE;
	cub->player.last_mouse_x = -1;
}

void	init_map(t_map *map)
{
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->floor_color = -1;
	map->ceil_color = -1;
	map->grid = NULL;
	map->player_dir = 0;
	map->width = 0;
	map->height = 0;
	map->doors = NULL;
	map->num_doors = 0;
}
