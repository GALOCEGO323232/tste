#include "cub3d_bonus.h"

static void	draw_minimap_pixel(t_cub *cub, int x, int y, int color);
static void	draw_minimap_tile(t_cub *cub, int mx, int my, char tile);
static void	draw_player_on_minimap(t_cub *cub);

void	render_minimap(t_cub *cub)
{
	int	map_y;
	int	map_x;

	if (!cub->map.minimap.enabled)
		return ;
	map_y = -1;
	while (++map_y < cub->map.height)
	{
		map_x = -1;
		while (++map_x < cub->map.width)
		{
			if (map_x * cub->map.minimap.scale >= MINIMAP_SIZE)
				break ;
			if (map_y * cub->map.minimap.scale >= MINIMAP_SIZE)
				break ;
			draw_minimap_tile(cub, map_x, map_y, cub->map.grid[map_y][map_x]);
		}
	}
	draw_player_on_minimap(cub);
}

static void	draw_minimap_tile(t_cub *cub, int mx, int my, char tile)
{
	int	screen_x;
	int	screen_y;
	int	color;
	int	i;
	int	j;

	if (tile == '1')
		color = MINIMAP_COLOR_WALL;
	else if (tile == '0' || is_player(tile) || tile == 'O')
		color = MINIMAP_COLOR_FLOOR;
	else if (tile == 'D')
		color = MINIMAP_COLOR_DOOR;
	else
		color = 0x000000;
	screen_x = mx * cub->map.minimap.scale;
	screen_y = my * cub->map.minimap.scale;
	i = -1;
	while (++i < cub->map.minimap.scale)
	{
		j = -1;
		while (++j < cub->map.minimap.scale)
			draw_minimap_pixel(cub, screen_x + i, screen_y + j, color);
	}
}

static void	draw_player_on_minimap(t_cub *cub)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = (int)(cub->player.pos_x * cub->map.minimap.scale);
	py = (int)(cub->player.pos_y * cub->map.minimap.scale);
	i = -2;
	while (++i <= 2)
	{
		j = -2;
		while (++j <= 2)
			draw_minimap_pixel(cub, px + i, py + j, MINIMAP_COLOR_PLAYER);
	}
}

static void	draw_minimap_pixel(t_cub *cub, int x, int y, int color)
{
	if (x >= 0 && x < MINIMAP_SIZE && y >= 0 && y < MINIMAP_SIZE)
		my_mlx_pixel_put(&cub->screen, x, y, color);
}
