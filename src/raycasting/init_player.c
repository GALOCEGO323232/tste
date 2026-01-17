/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgagliar <kgagliar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/01/17 14:39:28 by kgagliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_cub *cub)
{
	cub->player.pos_x = cub->map.player_x + 0.5;
	cub->player.pos_y = cub->map.player_y + 0.5;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	if (cub->map.player_dir == 'N')
	{
		cub->player.dir_y = -1;
		cub->player.plane_x = 0.66;
	}
	else if (cub->map.player_dir == 'S')
	{
		cub->player.dir_y = 1;
		cub->player.plane_x = -0.66;
	}
	else if (cub->map.player_dir == 'E')
	{
		cub->player.dir_x = 1;
		cub->player.plane_y = 0.66;
	}
	else if (cub->map.player_dir == 'W')
	{
		cub->player.dir_x = -1;
		cub->player.plane_y = -0.66;
	}
}
