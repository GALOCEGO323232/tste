#include "cub3d_bonus.h"

void	toggle_minimap(t_cub *cub)
{
	cub->map.minimap.enabled = !cub->map.minimap.enabled;
}
