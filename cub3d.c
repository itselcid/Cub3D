#include "cub3d.h"

int map[MAP_ROWS][MAP_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

t_game game;

void ft_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    dst = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void ft_draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
{
    double distance_x = end_x - start_x;
    double distance_y = end_y - start_y;
    double total_steps;

    if (fabs(distance_x) > fabs(distance_y))
        total_steps = fabs(distance_x);
    else
        total_steps = fabs(distance_y);

    double x_increment = distance_x / total_steps;
    double y_increment = distance_y / total_steps;

    double current_x = start_x;
    double current_y = start_y;

    int step = 0;
    while (step <= total_steps)
    {
        ft_mlx_pixel_put(game, current_x, current_y, color);
        current_x += x_increment;
        current_y += y_increment;
        step++;
    }
}

int ft_init_window(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error initializing MLX.\n");
        return 0;
    }
    game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cube3D");
    if (!game->win)
    {
        printf("Error creating MLX window.\n");
        return 0;
    }
    game->img.img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
    return 1;
}

void ft_initialize()
{
    game.player.x = WINDOW_WIDTH / 2;
    game.player.y = WINDOW_HEIGHT / 2;
    game.player.width = 1;
    game.player.height = 1;
    game.player.turn_direction = 0;
    game.player.walk_direction = 0;
    game.player.rotation_angle = PI / 2;
    game.player.walk_speed = 1;           
    game.player.turn_speed = 0.02;        
}

void ft_move_player()                  
{
    float   move_step;
    float   new_x;
    float   new_y;
    int     map_x;
    int     map_y;

    game.player.rotation_angle += game.player.turn_direction * game.player.turn_speed;
    move_step = game.player.walk_direction * game.player.walk_speed;

    new_x = game.player.x + cos(game.player.rotation_angle) * move_step;
    new_y = game.player.y + sin(game.player.rotation_angle) * move_step;

    map_x = (int)(new_x / SQUARE_SIZE);
    map_y = (int)(new_y / SQUARE_SIZE);

    if (!map[map_y][map_x])
    {
        game.player.x = new_x;
        game.player.y = new_y;
    }
}

void ft_draw_player()
{
    int x = game.player.x;
    int y = game.player.y;
    int i = -2;
    while (i < 2)
    {
        int j = -2;
        while (j < 2)
        {
            ft_mlx_pixel_put(&game, x + i, y + j, 0xFFFFFF);
            j++;
        }
        i++;
    }

    ft_draw_line(
        &game,
        x,
        y,
        x + cos(game.player.rotation_angle) * 40,
        y + sin(game.player.rotation_angle) * 40,
        0xFF0000);
}

void ft_draw_map()
{
    int square_color;
    int i = 0;
    while (i < MAP_ROWS)
    {
        int j = 0;
        while (j < MAP_COLS)
        {
            int square_x = j * SQUARE_SIZE;
            int square_y = i * SQUARE_SIZE;
            if (map[i][j] != 0)
                square_color = 0xFFFFFF;
            else
                square_color = 0x000000;
            int y = 0;
            while (y < SQUARE_SIZE)
            {
                int x = 0;
                while (x < SQUARE_SIZE)
                {
                    ft_mlx_pixel_put(&game, square_x + x, square_y + y, square_color);
                    x++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
}

int ft_key_press(int keycode)
{
    if (keycode == 65307)
        exit(0);
    if (keycode == 65362)
        game.player.walk_direction = +1;
    if (keycode == 65364)
        game.player.walk_direction = -1;
    if (keycode == 65363)
        game.player.turn_direction = +1;
    if (keycode == 65361)
        game.player.turn_direction = -1;
    return 0;
}

int ft_key_release(int keycode)
{
    if (keycode == 65362 || keycode == 65364)
        game.player.walk_direction = 0;
    if (keycode == 65363 || keycode == 65361)
        game.player.turn_direction = 0;
    return 0;
}

int ft_game_loop(t_game *game)
{
    ft_move_player();                  
    ft_draw_map();
    ft_draw_player();
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return 0;
}

int main()
{
    if (!ft_init_window(&game))
        return 1;
    ft_initialize();
    mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game);
    mlx_loop_hook(game.mlx, (int (*)(void *))ft_game_loop, &game);
    mlx_loop(game.mlx);

    return 0;
}
