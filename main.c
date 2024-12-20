#include "cub3d.h"
int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "Error\n Invalid number of arguments", 36);
		return (1);
	}
	if (!check_file_extension(av[1]))
	{
		write(1, "Error\n Invalid file extension", 30);
		return (1);
	}
	if (!ft_init_window(&game))
		return 1;
	ft_initialize();
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
	mlx_loop_hook(game.mlx, (int (*)(void *))ft_game_loop, &game);
	mlx_loop(game.mlx);

	return 0;
}