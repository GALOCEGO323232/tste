/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/01/10 11:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (check_args(argc, argv))
		return (1);
	if (parse_cub_file(argv[1], &cub))
		return (1);
	
	cub.mlx = mlx_init();
	if (!cub.mlx)
		return (error_exit("Error\nMLX Init failed\n"), 1);
	cub.win = mlx_new_window(cub.mlx, 800, 600, "cub3D");
	if (!cub.win)
		return (error_exit("Error\nMLX Window failed\n"), 1);

	init_textures(&cub);
	// Init player
	init_player(&cub);

	// Hooks
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	mlx_key_hook(cub.win, key_press, &cub);
	mlx_loop_hook(cub.mlx, render_loop, &cub);

	mlx_loop(cub.mlx);
	
	// Cleanup and exit - Todo: Free map and textures logic
	return (0);
}
