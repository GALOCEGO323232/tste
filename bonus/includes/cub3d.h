#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include "structs.h"

# define ERR_ARGS "Error\nInvalid number of arguments\n"
# define ERR_EXT "Error\nInvalid file extension\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_MALLOC "Error\nMalloc failed\n"
# define ON_DESTROY 17
# define ON_KEYPRESS 2
# define KEY_A 97
# define KEY_D 100
# define KEY_DOWN 65364
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_S 115
# define KEY_UP 65362
# define KEY_W 119
# define WIN_HEIGHT 600
# define WIN_WIDTH 800

int		add_line_to_list(t_list **map_lines, char *line);
void	calc_step(t_cub *cub, t_ray *ray);
void	calc_wall_height(t_cub *cub, t_ray *ray);
void	calculate_new_position(t_cub *cub, double *new_x, double *new_y,
			int direction);
int		check_args(int argc, char **argv);
int		check_walls(t_map *map);
void	cleanup_cub(t_cub *cub);
int		cleanup_cub_return(t_cub *cub);
void	cleanup_map_lines(t_list **map_lines);
int		cleanup_parse_error(t_cub *cub, t_list **map_lines);
int		close_window(t_cub *cub);
char	**convert_list_to_array(t_list *map_lines, t_map *map);
char	**copy_grid_padded(t_map *map);
void	draw_ceiling(t_cub *cub, int x, int draw_start);
void	draw_column(t_cub *cub, int x, t_ray *ray);
void	draw_floor(t_cub *cub, int x, int draw_end);
void	draw_wall(t_cub *cub, int x, t_ray *ray);
void	error_exit(char *msg);
void	error_exit_cleanup(t_cub *cub, char *msg);
void	free_grid(char **grid);
int		handle_movement_keys(int keycode, t_cub *cub);
void	init_cub(t_cub *cub);
void	init_map(t_map *map);
void	init_player(t_cub *cub);
void	init_ray(t_cub *cub, t_ray *ray, int x);
void	init_textures(t_cub *cub);
int		is_player(char c);
int		is_valid_char(char c);
int		key_press(int keycode, t_cub *cub);
int		mark_adjacent_cells(t_flood_params *params, int x, int y);
void	move_player(t_cub *cub, double move_speed, int direction);
void	my_mlx_pixel_put(t_screen *screen, int x, int y, int color);
int		parse_cub_file(char *file, t_cub *cub);
int		parse_line(char *line, t_cub *cub);
int		parse_rgb(char *line);
void	perform_dda(t_cub *cub, t_ray *ray);
int		raycast(t_cub *cub);
int		read_map(int fd, char *first_line, t_cub *cub, t_list **map_lines);
int		read_remaining_lines(int fd, t_list **map_lines);
int		render_loop(t_cub *cub);
void	rotate_player(t_cub *cub, double rot_speed);
void	select_texture(t_cub *cub, t_ray *ray);
int		validate_map(t_map *map);
int		key_release(int keycode, t_cub *cub);

#endif
