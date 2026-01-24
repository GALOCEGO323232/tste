#include "cub3d_bonus.h"

void	calc_sprite_transform(t_cub *cub, t_sprite_calc *sc,
			t_sprite_pos *sprite)
{
	sc->sprite_x = sprite->x - cub->player.pos_x;
	sc->sprite_y = sprite->y - cub->player.pos_y;
	sc->inv_det = 1.0 / (cub->player.plane_x * cub->player.dir_y
			- cub->player.dir_x * cub->player.plane_y);
	sc->transform_x = sc->inv_det * (cub->player.dir_y * sc->sprite_x
			- cub->player.dir_x * sc->sprite_y);
	sc->transform_y = sc->inv_det * (-cub->player.plane_y * sc->sprite_x
			+ cub->player.plane_x * sc->sprite_y);
	sc->screen_x = (int)((WIN_WIDTH / 2) * (1 + sc->transform_x
				/ sc->transform_y));
	sc->height = abs((int)(WIN_HEIGHT / sc->transform_y));
	sc->width = abs((int)(WIN_HEIGHT / sc->transform_y));
}

void	calc_sprite_screen(t_sprite_calc *sc, t_sprite_draw *sd)
{
	sd->start_y = -sc->height / 2 + WIN_HEIGHT / 2;
	if (sd->start_y < 0)
		sd->start_y = 0;
	sd->end_y = sc->height / 2 + WIN_HEIGHT / 2;
	if (sd->end_y >= WIN_HEIGHT)
		sd->end_y = WIN_HEIGHT - 1;
	sd->start_x = -sc->width / 2 + sc->screen_x;
	if (sd->start_x < 0)
		sd->start_x = 0;
	sd->end_x = sc->width / 2 + sc->screen_x;
	if (sd->end_x >= WIN_WIDTH)
		sd->end_x = WIN_WIDTH - 1;
}

int	update_animation_frame(void)
{
	static struct timeval	last_time;
	static int				frame;
	struct timeval			curr_time;
	long					ms;

	gettimeofday(&curr_time, NULL);
	ms = (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000)
		- (last_time.tv_sec * 1000 + last_time.tv_usec / 1000);
	if (ms > 200)
	{
		frame = (frame + 1) % 4;
		last_time = curr_time;
	}
	return (frame);
}
