#include "cub3d.h"

static int	ft_close_window(void)
{
	exit(0);
	return (0);
}

int main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
	{
		write(1, "Error\nInvalid number of arguments\n", 35);
		return (1);
	}

	if (parse_map(&game, av[1]))
		return 1;

	if (!ft_init_window(&game))
		return 1;

	ft_initialize(&game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
	mlx_hook(game.win, 17, 0, ft_close_window, 0); 
	mlx_loop_hook(game.mlx, (int (*)(void *))ft_game_loop, &game);
	mlx_loop(game.mlx);

	cleanup_up(&game, 0);
	return 0;
}