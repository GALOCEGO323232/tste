#include "cub3d.h"

static void	init_mlx(t_cub *cub);
static int	init_screen(t_cub *cub);

int	main(int argc, char **argv)
{
	t_cub	cub;

	init_cub(&cub);
	if (check_args(argc, argv))
		return (1);
	if (parse_cub_file(argv[1], &cub))
		return (cleanup_cub_return(&cub));
	init_mlx(&cub);
	init_textures(&cub);
	init_player(&cub);
	mlx_hook(cub.win, 17, 0, close_window, &cub);
	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub);
	mlx_loop_hook(cub.mlx, render_loop, &cub);
	mlx_loop(cub.mlx);
	return (0);
}

static int	init_screen(t_cub *cub)
{
	cub->screen.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->screen.img)
		return (1);
	cub->screen.addr = mlx_get_data_addr(cub->screen.img, &cub->screen.bpp,
			&cub->screen.line_len, &cub->screen.endian);
	if (!cub->screen.addr)
		return (1);
	return (0);
}

static void	init_mlx(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		error_exit_cleanup(cub, "Error\nMLX Init failed\n");
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!cub->win)
		error_exit_cleanup(cub, "Error\nMLX Window failed\n");
	if (init_screen(cub))
		error_exit_cleanup(cub, "Error\nScreen buffer init failed\n");
}
