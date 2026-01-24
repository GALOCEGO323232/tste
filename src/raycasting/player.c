#include "cub3d.h"

static void	set_north_direction(t_player *player);
static void	set_south_direction(t_player *player);
static void	set_east_direction(t_player *player);
static void	set_west_direction(t_player *player);

void	init_player(t_cub *cub)
{
	cub->player.pos_x = cub->map.player_x + 0.5;
	cub->player.pos_y = cub->map.player_y + 0.5;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	if (cub->map.player_dir == 'N')
		set_north_direction(&cub->player);
	else if (cub->map.player_dir == 'S')
		set_south_direction(&cub->player);
	else if (cub->map.player_dir == 'E')
		set_east_direction(&cub->player);
	else if (cub->map.player_dir == 'W')
		set_west_direction(&cub->player);
}

static void	set_north_direction(t_player *player)
{
	player->dir_y = -1;
	player->plane_x = 0.66;
}

static void	set_south_direction(t_player *player)
{
	player->dir_y = 1;
	player->plane_x = -0.66;
}

static void	set_east_direction(t_player *player)
{
	player->dir_x = 1;
	player->plane_y = 0.66;
}

static void	set_west_direction(t_player *player)
{
	player->dir_x = -1;
	player->plane_y = -0.66;
}
