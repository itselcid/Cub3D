
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

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    dst = game->img.addr + (y * game->img.line_length + x * (game->img.bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_line(t_game *game, int start_x, int start_y, int end_x, int end_y, int color)
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
        my_mlx_pixel_put(game, current_x, current_y, color);
        current_x += x_increment;
        current_y += y_increment;
        step++;
    }
}

int initializeWindow(t_game *game)
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

void setup()
{
    game.player.x = WINDOW_WIDTH / 2;
    game.player.y = WINDOW_HEIGHT / 2;
    game.player.width = 1;
    game.player.height = 1;
    game.player.turnDirection = 0;
    game.player.walkDirection = 0;
    game.player.rotationAngle = PI / 2;
    game.player.walkSpeed = 30;
    game.player.turnSpeed = 45 * (PI / 180);
}

int mapHasWallAt(float x, float y)
{
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
    {
        return 1;
    }
    int mapGridIndexX = floor(x / SQUARE_SIZE);
    int mapGridIndexY = floor(y / SQUARE_SIZE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
}

void move_player(float delta_time)
{
    game.player.rotationAngle += game.player.turnDirection * game.player.turnSpeed * delta_time;
    float moveStep = game.player.walkDirection * game.player.walkSpeed * delta_time;

    float newPlayerX = game.player.x + cos(game.player.rotationAngle) * moveStep;
    float newPlayerY = game.player.y + sin(game.player.rotationAngle) * moveStep;

    if (!mapHasWallAt(newPlayerX, newPlayerY))
    {
        game.player.x = newPlayerX;
        game.player.y = newPlayerY;
    }
}

void draw_player()
{
    int x = game.player.x;
    int y = game.player.y;
    int i = -2;
    while (i < 2)
    {
        int j = -2;
        while (j < 2)
        {
            my_mlx_pixel_put(&game, x + i, y + j, 0xFFFFFF);
            j++;
        }
        i++;
    }

    draw_line(
        &game,
        x,
        y,
        x + cos(game.player.rotationAngle) * 40,
        y + sin(game.player.rotationAngle) * 40,
        0xFF0000);
}

void draw_map()
{
    int squareColor;
    int i = 0;
    while (i < MAP_ROWS)
    {
        int j = 0;
        while (j < MAP_COLS)
        {
            int squareX = j * SQUARE_SIZE;
            int squareY = i * SQUARE_SIZE;
            if (map[i][j] != 0)
                squareColor = 0xFFFFFF;
            else
                squareColor = 0x000000;
            int y = 0;
            while (y < SQUARE_SIZE)
            {
                int x = 0;
                while (x < SQUARE_SIZE)
                {
                    my_mlx_pixel_put(&game, squareX + x, squareY + y, squareColor);
                    x++;
                }
                y++;
            }
            j++;
        }
        i++;
    }
}

int key_press(int keycode)
{
    if (keycode == 65307)
        exit(0);
    if (keycode == 65362)
        game.player.walkDirection = +1;
    if (keycode == 65364)
        game.player.walkDirection = -1;
    if (keycode == 65363)
        game.player.turnDirection = +1;
    if (keycode == 65361)
        game.player.turnDirection = -1;
    return 0;
}

int key_release(int keycode)
{
    if (keycode == 65362 || keycode == 65364)
        game.player.walkDirection = 0;
    if (keycode == 65363 || keycode == 65361)
        game.player.turnDirection = 0;
    return 0;
}

int game_loop(t_game *game)
{
    float delta_time = 1.0 / FPS;

    move_player(delta_time);
    draw_map();
    draw_player();
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    return 0;
}

int main()
{
    if (!initializeWindow(&game))
        return 1;
    setup();
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    mlx_loop_hook(game.mlx, (int (*)(void *))game_loop, &game);
    mlx_loop(game.mlx);

    return 0;
}
