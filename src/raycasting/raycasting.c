#include "cub3d.h"

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
	// Texture specific
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray;

static void	init_ray(t_cub *cub, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)800 - 1; // 800 is width
	ray->ray_dir_x = cub->player.dir_x + cub->player.plane_x * ray->camera_x;
	ray->ray_dir_y = cub->player.dir_y + cub->player.plane_y * ray->camera_x;
	ray->map_x = (int)cub->player.pos_x;
	ray->map_y = (int)cub->player.pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	calc_step(t_cub *cub, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub->player.pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub->player.pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_cub *cub, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall_height(t_cub *cub, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(600 / ray->perp_wall_dist); // 600 is height
	ray->draw_start = -ray->line_height / 2 + 600 / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + 600 / 2;
	if (ray->draw_end >= 600)
		ray->draw_end = 600 - 1;
	if (ray->side == 0)
		ray->wall_x = cub->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = cub->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 3; // EA
		else
			ray->tex_num = 2; // WE
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 1; // SO
		else
			ray->tex_num = 0; // NO
	}
	ray->tex_x = (int)(ray->wall_x * (double)cub->map.textures[ray->tex_num].width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = cub->map.textures[ray->tex_num].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = cub->map.textures[ray->tex_num].width - ray->tex_x - 1;
	ray->step = 1.0 * cub->map.textures[ray->tex_num].height / ray->line_height;
	ray->tex_pos = (ray->draw_start - 600 / 2 + ray->line_height / 2) * ray->step;
}

// Unsafe pixel put (direct address would be faster)
// But we are using mlx_pixel_put which is safe but slow.
// We must implement an image buffer for the screen to be performant.
// For now, let's just make it work logically.

static void	draw_column(t_cub *cub, int x, t_ray *ray)
{
	int		y;
	int		color;
	int		tex_y;
	t_img	*tex;

	tex = &cub->map.textures[ray->tex_num];
	
	// Ceiling
	y = 0;
	while (y < ray->draw_start)
	{
		mlx_pixel_put(cub->mlx, cub->win, x, y, cub->map.ceil_color);
		y++;
	}

	// Wall
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (tex->height - 1);
		ray->tex_pos += ray->step;
		
		// get color from texture at tex_x, tex_y
		// addr + (y * line_len + x * (bpp / 8))
		char *dst = tex->addr + (tex_y * tex->line_len + ray->tex_x * (tex->bpp / 8));
		color = *(unsigned int*)dst;
		
		mlx_pixel_put(cub->mlx, cub->win, x, y, color);
		y++;
	}

	// Floor
	while (y < 600)
	{
		mlx_pixel_put(cub->mlx, cub->win, x, y, cub->map.floor_color);
		y++;
	}
}

int	raycast(t_cub *cub)
{
	int		x;
	t_ray	ray;

	// Note: We are using mlx_pixel_put directly on window which is slow and causes flickering.
	// But it verifies logic.
	
	x = 0;
	while (x < 800)
	{
		init_ray(cub, &ray, x);
		calc_step(cub, &ray);
		perform_dda(cub, &ray);
		calc_wall_height(cub, &ray);
		draw_column(cub, x, &ray);
		x++;
	}
	return (0);
}
