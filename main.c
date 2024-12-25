#include "cub3d.h"

t_game game;

int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(1, "Error\nInvalid number of arguments\n", 35);
        return (1);
    }

    if (parse_map(av[1]))
        return 1;
        
    // if (!ft_init_window(&game))
    //     return 1;
        
    // ft_initialize();
    // mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
    // mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
    // mlx_loop_hook(game.mlx, (int (*)(void *))ft_game_loop, &game);
    // mlx_loop(game.mlx);

    return 0;
}