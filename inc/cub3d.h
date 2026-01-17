/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/01/10 11:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "structs.h"

// Error messages
# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_EXT "Error\nInvalid file extension\n"
# define ERR_MALLOC "Error\nMalloc failed\n"

// Parsing
int		check_args(int argc, char **argv);
int		parse_cub_file(char *file, t_cub *cub);
int		parse_line(char *line, t_cub *cub);
int		read_map(int fd, char *first_line, t_cub *cub, t_list **map_lines);
int		validate_map(t_map *map);

// Input
int		close_window(t_cub *cub);
int		key_press(int keycode, t_cub *cub);

// Raycasting
void	init_player(t_cub *cub);
int		raycast(t_cub *cub);

// Rendering
void	init_textures(t_cub *cub);
int		render_loop(t_cub *cub);

// Utils
void	error_exit(char *msg);

#endif
