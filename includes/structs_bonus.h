#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_screen
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_screen;

typedef struct s_minimap
{
	int		enabled;
	int		size;
	int		scale;
}	t_minimap;

typedef struct s_door
{
	int		x;
	int		y;
	int		is_open;
	float	open_offset;
}	t_door;

typedef struct s_sprite_pos
{
	double	x;
	double	y;
	double	dist;
}	t_sprite_pos;

typedef struct s_map
{
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	int				floor_color;
	int				ceil_color;
	char			**grid;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	char			player_dir;
	t_img			textures[4];
	t_img			sprite_frames[4];
	t_minimap		minimap;
	t_door			*doors;
	int				num_doors;
	t_sprite_pos	*sprites;
	int				num_sprites;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		last_mouse_x;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
	int		up;
	int		down;
}	t_keys;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_screen	screen;
	t_keys		keys;
}	t_cub;

typedef struct s_flood_params
{
	char	**grid;
	int		height;
	int		width;
}	t_flood_params;

typedef struct s_sprite_calc
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		height;
	int		width;
}	t_sprite_calc;

typedef struct s_sprite_draw
{
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
}	t_sprite_draw;

#endif
